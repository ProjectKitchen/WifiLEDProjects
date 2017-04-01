// when using the AI-Thinker ESP12 boards, 
// select NodeMCU 0.9 (ESP12-Module) in tools->board

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "font5x7.h"

#define PIN_BUTTON  0    // marked as D3 on AI-Thinker ESP12 board !
#define PIN_LED     5    // marked as D1 on AI-Thinker ESP12 board !

#define NUM_COLUMNS 8    // put number of stripes (columns) here !
#define NUM_LEDS    NUM_COLUMNS*7   // 7 rows per column

#define MODE_WIPE    0
#define MODE_RAINBOW 1
#define MODE_SCROLL  2
#define MODE_IDLE    3

String scrolltext = "  Hello World !!  WiFiLED Demo !  ";
uint16_t scrollwait = 55;
uint32_t scrollcolor = 0x808000;
byte scrollindex = 0; // scroll character index

// Neopixel object
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

byte demo_index = MODE_WIPE;  // default mode
byte brightness = 50;         // default brightness
uint32_t pixels[NUM_LEDS];    // pixel buffer. this buffer allows you to set arbitrary
                              // brightness without destroying the original color values

ESP8266WebServer server(80);  // create web server at HTTP port 80

// Forward declare functions
String get_ap_name();
void button_handler();
void on_status();
void on_change_color();
void on_homepage();
void show_leds();
void demo_wipe();
void demo_rainbow();
void demo_scrolltext();

void show_leds() {
  uint32_t r, g, b;
  uint32_t c;
  for(int i=0;i<NUM_LEDS;i++) {
    r = (pixels[i]>>16)&0xFF;
    g = (pixels[i]>>8)&0xFF;
    b = (pixels[i])&0xFF;
    r = r*brightness/255;
    g = g*brightness/255;
    b = b*brightness/255;
    c = (r<<16) + (g<<8) + b;
    leds.setPixelColor(i, c);
  }
  leds.show();
}

void setup() {
  Serial.begin(115200);
  
  // Set pin mode
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED,    OUTPUT);

  // Initialize LEDs
  leds.begin();
  leds.show();

  // Set WiFi SSID
  String ap_name = get_ap_name();
  WiFi.persistent(false);
  WiFi.softAP(ap_name.c_str());
  WiFi.mode(WIFI_AP);
  
  // Set server callback functions
  server.on("/",   on_homepage);    
  server.on("/js", on_status);
  server.on("/cc", on_change_color);
  server.begin();
  
  // Set button handler
  attachInterrupt(PIN_BUTTON, button_handler, FALLING);
}

// The variable below is modified by interrupt service routine
// so declare it as volatile
volatile boolean button_clicked = false;

void loop() {
  server.handleClient();
  switch(demo_index) {
  case MODE_WIPE:
    demo_wipe();
    break;
    
  case MODE_RAINBOW:
    demo_rainbow();
    break;

  case MODE_SCROLL:
    if(scrolltext.length() > 0) {
      demo_scrolltext();
    }
    break;

  case MODE_IDLE:
    break;

  default: demo_index=0;
    break;
  }   
  
  if(button_clicked) {
    demo_index ++;  // upon button click, proceed to the next demo
    button_clicked = false;
  }
}

/* ----------------
 * Color Wipe Demo
 * ---------------- */

int wipe(uint32_t c, byte wait) {  // wipe with a given color
  static int actled=0;
  leds.setPixelColor(actled, c);
  leds.show();
  delay(wait);
  actled++; if (actled>=NUM_LEDS) actled=0;
  return (actled);
}

void demo_wipe() {
  static byte idx = 0;
  if (!(wipe((uint32_t)brightness<<(8*idx), scrollwait)))
    idx=(idx+1)%3;
}

/* ----------------
 *   Rainbox Demo
 * ---------------- */

uint32_t wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return leds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return leds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void demo_rainbow() {
  static byte idx = 0;
  for(int i=0;i<NUM_LEDS;i++) {
    pixels[i] = wheel((i+idx)&0xFF);
  }
  show_leds();
  delay(scrollwait);
  idx++;
}

/* ----------------
 * Scroll Text Demo
 * ---------------- */

void drawCol(char c, int i){
  int pos;
  if(i >= 0 && i < NUM_COLUMNS){
    for(int j = 0; j < 7; j++){
        if (!(i%2)) pos=6-j; else pos=j; // reverse every second column !
        if(c & 0x1){
//          leds.setPixelColor(i*7+pos, scrollcolor);
            pixels[i*7+pos]=scrollcolor;
        } else {
//          leds.setPixelColor(i*7+pos, 0);
            pixels[i*7+pos]=0;
        }
        c >>= 1;
    }
  }
}

void drawChar(char c, int offset){
  char col;
  for(int i = 0; i < 5; i++){
    if(i - offset >= 0 && i - offset < NUM_COLUMNS){
      col = pgm_read_byte(font+(c*5)+i);
      drawCol(col,i - offset);
    }
  }
}

void demo_scrolltext() {

  for(byte j = 0; j < 6; j++){
    for(byte k = 0; k < (NUM_COLUMNS/5)+1; k++){
      drawChar(scrolltext.charAt(scrollindex+k),j - k*6);
      drawCol(0,5-j+k*6);
    }
    delay(scrollwait);  
//    leds.show();
    show_leds();
  }

  scrollindex = (scrollindex+1)%scrolltext.length();
}

/* ----------------
 *  WebServer Demo
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
  html += "}";
  server.send(200, "text/html", html);
}

void on_change_color() {
  uint16_t i;
  if(server.hasArg("pixels")) {
    String val = server.arg("pixels");
//    for(i=0;i<NUM_LEDS;i++) {
    for(i=0;i<35;i++) {
      // every pixel color is 6 bytes storing the hex value
      // pixels are specified in row-major order
      // here we need to flip it to column-major order to 
      // match the physical connection of the leds
      byte r=i/5, c=i%5;
      if (!(c%2)) r=6-r;   // reverse every second column !
      pixels[c*7+r] = strtol(val.substring(i*6, i*6+6).c_str(), NULL, 16);
    }
    show_leds();
    demo_index=MODE_IDLE;
  }
  if(server.hasArg("clear")) {
    for(i=0;i<NUM_LEDS;i++) {
      pixels[i] = 0;
    }
    show_leds();
    demo_index=MODE_IDLE;
  }
  if(server.hasArg("brightness")) {
    brightness = server.arg("brightness").toInt();
    show_leds();
  }
  if(server.hasArg("wait")) {
    scrollwait = server.arg("wait").toInt();
    if(scrollwait<3) scrollwait=3;
  }
  if(server.hasArg("color")) {
    scrollcolor = strtol(server.arg("color").c_str(), NULL, 16);
  }
  if(server.hasArg("scrolltext")) {
    scrolltext = server.arg("scrolltext");
    scrolltext = " "+scrolltext;
    demo_index=MODE_SCROLL;
    scrollindex = 0;
  }
  server.send(200, "text/html", "{\"result\":1}");
}

char dec2hex(byte dec) {
  if(dec<10) return '0'+dec;
  else return 'A'+(dec-10);
}

// AP name is ESP_ following by 
// the last 6 bytes of MAC address
String get_ap_name() {
  static String ap_name = "LedScrollBoard";
  if(!ap_name.length()) {
    byte mac[6];
    WiFi.macAddress(mac);
    ap_name = "ESP_";
    for(byte i=3;i<6;i++) {
      ap_name += dec2hex((mac[i]>>4)&0x0F);
      ap_name += dec2hex(mac[i]&0x0F);
    }
  }
  return ap_name;
}

void button_handler() {
  button_clicked = true;
}


