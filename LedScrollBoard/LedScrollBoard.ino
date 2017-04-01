//
// LedScrollBoard V1.0
//  
// ESP8266 firmware and web inteface for scrolltext / pixel editor  
// based on the WiFi-enabled Led Workshop by Rui (Ray) Wang - thanks to Ray !!
// visit: rayshobby.net/?p=10963   watch: https://www.youtube.com/watch?v=ZKuIWDocIiM
// 
// adapted for AI-Thinker ESP12 boards + WS2812 led pixels by chris veigl / chris@shifz.org
// additional features: 
// DNS/captive portal, big scrollboard size, icon animations, brightness & scroll speed control
//
// select NodeMCU 0.9 (ESP12-Module) in tools->board
// connect led pixels to GPIO3 (RX-Pin ! used for DMA-supported output by NeoPixelBus lilbrary) 
// connect a potentiometer for max brightness control to A0 
// connect an led to Pin5 (D1) to indicate main loop operation
// connect a momentary switch to Pin4 (D2) - when pressed at startup/reset, captive portal/DNS is not used
//

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <NeoPixelBus.h>
#include "font5x7.h"

#define BIG_BOARD
// #define UNIQUE_AP_NAME    // uncomment this if you want to use multiple boards 

#define PIN_BUTTON  4    // marked as D2 on AI-Thinker ESP12 board !
#define PIN_LED     5    // marked as D1 on AI-Thinker ESP12 board !

#ifdef BIG_BOARD
  #define NUM_COLUMNS 41    // big board hast 41 columns 
  #define ICON_OFFSET 44
#else
  #define NUM_COLUMNS 8     // small demo board has 8 columns 
  #define ICON_OFFSET 6
#endif  

#define NUM_LEDS    NUM_COLUMNS*7   // 7 leds (rows) per column

#define MAX_ICONS 10
#define ICON_PIXELS 35   // number of LED pixels per icon (5 x 7)

#define BG_MODE_FILL    0   // background modes
#define BG_MODE_RAINBOW 1

// Neopixel object
// this uses GPIO3 (marked as RX on the AT-Thinker ESP12 board)
// this is a hardware restriction because of DMA access, see NeoPixelBus documentation!
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> leds(NUM_LEDS);

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(192, 168, 4, 1);   // Private network for server

ESP8266WebServer server(80);  // create web server at HTTP port 80
DNSServer        dnsServer;   // create the DNS object
byte serve_dns_requests=1;    // shall we react (captive portal)

byte bg_mode = BG_MODE_RAINBOW;
byte bg_brightness = 30;
uint16_t bg_wait = 20;
uint32_t bg_color = 0x0000a0;

String scrolltext = "       hello !  this is the open led billboard.    to post your message: connect to WiFi LedScrollBoard !      ";
byte scrollindex = 0;
byte scroll_mode=1;
byte scroll_brightness = 200;
uint16_t scrollwait = 40;
uint32_t scrollcolor = 0xa0a000;

uint32_t icons[MAX_ICONS][ICON_PIXELS+1] = { 0 }; // icon buffer. this holds up to 10 icons
uint16_t anim_wait = 100;
uint16_t icon_pos=0;
uint16_t preview_acticon=0;
byte act_icon=0,act_anim=0;
byte icon_brightness = 200; 

byte pixelupdate =1;
byte brightness = 80;         // default overall brightness
byte get_brightness_web = 0;  // default: set brightness from adc/potentiomenter
uint32_t pixels[NUM_LEDS];    // pixel buffer. this buffer allows you to set arbitrary

                              // brightness without destroying the original color values
// Forward declare functions
String get_ap_name();
void button_handler();
void on_status();
void on_change_color();
void on_background();
void on_scroll();
void on_icon();
void on_homepage();
void show_leds();
void background_rainbow();
void update_background();
void update_scrolltext();
void update_icons();
void load_iconPixels(byte);
uint32_t adjust_brightness(uint32_t, byte);

uint32_t counter=0;
byte ledstate=0;

// The variable below is modified by interrupt service routine
// so declare it as volatile
volatile boolean button_clicked = false;

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  //  Serial.setDebugOutput(true);
  //  Serial.println("\nESP8266 hotspot ready !");

  // Set pin mode
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED,    OUTPUT);

  // Set WiFi SSID
  String ap_name = get_ap_name();
  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ap_name.c_str());

  // WiFi.printDiag(Serial);
  // IPAddress myIP = WiFi.softAPIP();
  // Serial.print("AP IP address: ");
  // Serial.println(myIP);
  
  // Set server callback functions
  server.onNotFound(on_homepage);
  server.on("/",   on_homepage);    
  server.on("/js", on_status);
  server.on("/cc", on_change_color);
  server.on("/bg", on_background);
  server.on("/ic", on_icon);
  server.on("/sc", on_scroll);
  server.begin();

  // press button on startup if you do not want a captive portal
  if (digitalRead(PIN_BUTTON) == LOW) { 
     serve_dns_requests=0;
     bg_mode = BG_MODE_FILL;
  } else {
     dnsServer.start(DNS_PORT, "*", apIP);
     serve_dns_requests=1;
     bg_mode = BG_MODE_RAINBOW;
  }
     
  // Set button handler
  attachInterrupt(PIN_BUTTON, button_handler, FALLING);

  // Initialize LEDs
  leds.Begin();
  leds.Show();
}

void loop() {
  
  if (serve_dns_requests)
    dnsServer.processNextRequest();

  server.handleClient();
  ledstate=!ledstate;
  digitalWrite(PIN_LED,ledstate);

  if(button_clicked) {
    bg_mode ++;  // upon button click, change background mode
    button_clicked = false;
    pixelupdate=1;
  }

  update_background();
  update_scrolltext();
  update_icons ();

  if (pixelupdate) {
    pixelupdate=0;
    show_leds();
  }

  if ((!(counter % 100)) && (!get_brightness_web)) {
    byte new_brightness=analogRead(A0)>>2;
    if (brightness!=new_brightness) {
      Serial.print("set brightness to "); 
      Serial.println(new_brightness);
    }
    brightness=new_brightness;
  }

  counter++;   // global counter for timing activities
  delay(2);

  // maybe add later: emergency handling / sw-"watchdog"
  // see: https://github.com/esp8266/Arduino/issues/1532
  // seems not necessary as stability improved afer switching to NeopixelBus library !

  // maybe add later: 
  // store settings / scroll + animation patterns to eeprom via admin command
}


/* ----------------
 *   Rainbow Effect
 * ---------------- */

uint32_t getRGBColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return adjust_brightness(getRGBColor(255 - WheelPos * 3, 0, WheelPos * 3),bg_brightness);  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return adjust_brightness(getRGBColor(0, WheelPos * 3, 255 - WheelPos * 3),bg_brightness);  }
  WheelPos -= 170;
  return adjust_brightness(getRGBColor(WheelPos * 3, 255 - WheelPos * 3, 0),bg_brightness);
}

void background_rainbow() {
  static byte idx = 0;

  if (!(counter%bg_wait)) { 
    idx++; pixelupdate=1; 
  }

  for(int i=0;i<NUM_LEDS;i++) {
    pixels[i] = wheel((i+idx)&0xFF);
  }
}


void update_background()  {
  switch(bg_mode) {
    case BG_MODE_FILL:
      for(int i=0;i<NUM_LEDS;i++) 
        pixels[i]=adjust_brightness(bg_color,bg_brightness);
      break;
      
    case BG_MODE_RAINBOW:
        background_rainbow();
      break;
  
    default: bg_mode=BG_MODE_FILL;
      break;
  }
}   

void blit_icon(byte icon, int pos) {
  uint16_t i,p;
  if (icon>=MAX_ICONS) return;
  for(i=0;i<ICON_PIXELS;i++) {
      p=pos*7+i; 
      if ((p>=0) && (p<NUM_LEDS))  {
        byte c=i/7, r=i%7;
        if (pos%2) r=6-r;   // reverse every second column !
        if (icons[icon][c*7+r])        
           pixels[pos*7+i]=adjust_brightness(icons[icon][c*7+r],icon_brightness);
      }
  }
}

void update_icons() {
  if (preview_acticon) {
    blit_icon(act_icon+act_anim, icon_pos);
    if (!(counter%anim_wait)) {
      // icon_pos=(icon_pos+1)%(NUM_COLUMNS+20);
      if (icons[act_icon][ICON_PIXELS]) act_anim++;
      else act_anim=0; 
    }
    preview_acticon--;
  }
}


/* ---------------------
 * Scroll Text and Icons
 * --------------------- */
 
void drawIcon(byte icon_num, int offset) {
  byte anim_count;
  anim_count=icons[icon_num][ICON_PIXELS]; 
  if (anim_count) {
    if (!(counter%anim_wait)) { 
      anim_count++; 
      if ((icon_num+anim_count>=MAX_ICONS) || (!(icons[icon_num+anim_count-1][ICON_PIXELS])))
         anim_count=1;
      icons[icon_num][ICON_PIXELS]=anim_count;
      pixelupdate=1;
    }
    blit_icon(icon_num+anim_count-1,NUM_COLUMNS-ICON_OFFSET-offset);
  }
  else blit_icon(icon_num,NUM_COLUMNS-ICON_OFFSET-offset);
}

void drawFontCol(char c, int i){
  int pos;
  if(i >= 0 && i < NUM_COLUMNS){
    for(int j = 0; j < 7; j++){
        if (!(i%2)) pos=6-j; else pos=j; // reverse every second column !
        if(c & 0x1){
            pixels[i*7+pos]=adjust_brightness(scrollcolor,scroll_brightness);
        } 
        c >>= 1;
    }
  }
}

void drawChar(char c, int offset){
  char col;
  if (c<20) drawIcon (c-10,offset); // not a readable ASCII-character -> must be icon number!
  else {
    for(int i = 0; i < 5; i++){
      if(i - offset >= 0 && i - offset < NUM_COLUMNS){
        col = pgm_read_byte(font+(c*5)+i);
        drawFontCol(col,i - offset);
      }
    }
  }
}

void update_scrolltext() {
  static byte pos_in_char=0;
  if (!scrolltext.length()) return;
  if (!(counter%scrollwait)) {
    pos_in_char=(pos_in_char+1)%6; 
    if (!pos_in_char) scrollindex = (scrollindex+1)%scrolltext.length();
    pixelupdate=1;
  }

  for(byte k = 0; k < (NUM_COLUMNS/5)+1; k++){
      drawChar(scrolltext.charAt(scrollindex+k),pos_in_char - k*6);
      drawFontCol(0,5-pos_in_char+k*6);
  }
}


/* ----------------
 *  WebServer 
 * ---------------- */

#include "html.h"
void on_homepage() {
  String html = FPSTR(index_html);
  server.send(200, "text/html", html);
}

// this returns device variables in JSON, e.g.
// {"pixels":xxxx,"blink":1}
void on_status() {
  String html = "";
  html += "{\"brightness\":";
  html += brightness; 
  html += ",\"act_icon\":";
  html += act_icon; 
  html += ",\"bg_brightness\":";
  html += bg_brightness; 
  html += ",\"scroll_brightness\":";
  html += scroll_brightness; 
  html += ",\"icon_brightness\":";
  html += icon_brightness; 
  html += "}";
  server.send(200, "text/html", html);
}

uint16_t scale_wait(int16_t val) {
  int16_t v=35-val;   // the max position of the speed slider is 30
  if (v<3) v=3;
  if (v>10) v=10+(v-10)*(v-10)*2;  // waittime progresses by ^2
  return((uint16_t)v);
}

byte scale_brightness(byte val) {
  if (val>10) return(10+(val-10)*(val-10)/1.8);
  return(val);
}

void on_background() {
  if(server.hasArg("mode")) {
    bg_mode = server.arg("mode").toInt();
  }
  if(server.hasArg("wait")) {
    bg_wait = scale_wait(server.arg("wait").toInt());
  }
  if(server.hasArg("color")) {
    bg_color = strtol(server.arg("color").c_str(), NULL, 16);
  }
  if(server.hasArg("brightness")) {
    bg_brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_icon() {
  if(server.hasArg("icon")) {
    act_icon = server.arg("icon").toInt()-1;
    if (act_icon<0) act_icon=0;
    if (act_icon>=MAX_ICONS) act_icon=MAX_ICONS-1;
  }
  if(server.hasArg("anim")) {
    icons[act_icon][ICON_PIXELS]= server.arg("anim").toInt();
  }
  if(server.hasArg("wait")) {
    anim_wait = scale_wait(server.arg("wait").toInt());
  }
  if(server.hasArg("pixels")) {
       load_iconPixels(act_icon);
       preview_acticon=200;
  }
  if(server.hasArg("brightness")) {
    icon_brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_scroll() {
  int iconpos=0;
  if(server.hasArg("scrolltext")) {
    scrolltext = server.arg("scrolltext");
    scrolltext = " "+scrolltext;
    // check for icon in scrolltext
    while ((iconpos=scrolltext.indexOf('$',iconpos)) > -1)
    {
       uint8_t c =scrolltext[iconpos+1];
       if ((c>='1') && (c<='9')) {         
          scrolltext[iconpos+1]= c-'0'+9;  // this will identify the icon number !          
          scrolltext.remove(iconpos,1);
       } else iconpos++;     
    }
    scrollindex = 0;
  }
  if(server.hasArg("wait")) {
    scrollwait = scale_wait(server.arg("wait").toInt());
  }
  if(server.hasArg("color")) {
    scrollcolor = strtol(server.arg("color").c_str(), NULL, 16);
  }
  if(server.hasArg("mode")) {
    scroll_mode = server.arg("mode").toInt();
  }
  if(server.hasArg("brightness")) {
    scroll_brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

void on_change_color() {
  uint16_t i;
  if(server.hasArg("pixels")) {
       load_iconPixels(0);
  }
  if(server.hasArg("brightness")) {
    get_brightness_web=1;
    brightness = scale_brightness(server.arg("brightness").toInt());
  }
  server.send(200, "text/html", "{\"result\":1}");
  pixelupdate=1;
}

/* ----------------
 *  Helper functions 
 * ---------------- */


void load_iconPixels(byte num) {
  String val = server.arg("pixels");
  for(uint16_t i=0;i<ICON_PIXELS;i++) {
    // every pixel color is 6 bytes storing the hex value
    // pixels are specified in row-major order
    // here we need to flip it to column-major order to 
    // match the physical connection of the leds
    byte r=i/5, c=i%5;
    if (!(c%2)) r=6-r;   // reverse every second column !
    icons[num][c*7+r] = strtol(val.substring(i*6, i*6+6).c_str(), NULL, 16);
  }
}

char dec2hex(byte dec) {
  if(dec<10) return '0'+dec;
  else return 'A'+(dec-10);
}

// AP name is ESP_ following by 
// the last 6 bytes of MAC address
String get_ap_name() {
 static String ap_name = "LedScrollBoard";

 #ifdef UNIQUE_AP_NAME 
    byte mac[6];
    WiFi.macAddress(mac);
    for(byte i=3;i<6;i++) {
      ap_name += dec2hex((mac[i]>>4)&0x0F);
      ap_name += dec2hex(mac[i]&0x0F);
    }
  #endif 
  return ap_name;
}

void button_handler() {
  button_clicked = true;
}

uint32_t adjust_brightness(uint32_t c, byte brightness) {
  uint32_t r, g, b;
    r = (c>>16)& 0xFF;
    g = (c>>8)& 0xFF;
    b = c & 0xFF;
    r = r*brightness/255;
    g = g*brightness/255;
    b = b*brightness/255;
    return ((r<<16) + (g<<8) + b);
}

void show_leds() {
  for(int i=0;i<NUM_LEDS;i++) {
    leds.SetPixelColor(i, RgbColor(HtmlColor(adjust_brightness(pixels[i],brightness))));
  }
  leds.Show();
}

