const char index_html[] PROGMEM = R"(
<html>
<head>
<title>WiFi LED Demo</title>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<style>
.color-sel { width: 24px; height: 24px; text-align: center;}
.pixel-sel { width: 48px; height: 48px; background-color: black; }
button { font-size: 16px; }
p { font-size:18px; font-style:normal; line-height:0px; }
table { border-color:lightgray; border-collapse:collapse; }
</style>
</head>

<body> <font face="arial">
<script>
const MAX_ICONS=10;
const ICON_PIXELS=35;
const NUM_ROWS=7;
const NUM_COLUMNS=5;
var nh=12,i,j,cc='rgb(255, 255, 255)';
var cc_elem;
function w(s) { document.write(s); }
function id(s){ return document.getElementById(s); }
function mark(e) {e.innerHTML='&#10004;';}
function cs_click(e) {
 var bg=e.target.style.backgroundColor;
 cc_elem.innerHTML='';
 mark(e.target);
 cc=bg;
 cc_elem=e.target;
}

w('<table border=1>');
idx=0;
for(i=0;i<2;i++) {
 w('<tr>');
 for(j=0;j<nh;j++,idx++) {
  w('<td class=color-sel id=cs'+idx+'></td>');
  var obj=id('cs'+idx);
  if(i==0) { var hue=(j/nh)*360; obj.style.background='hsl('+hue+',100%,50%)'; }
  else { var lit=(j/(nh-1))*100; obj.style.background='hsl(0,0%,'+lit+'%)'; }
  obj.addEventListener('click',cs_click);
 }
 w('</tr>');
}
w('</table>');
cc_elem=id('cs'+(2*nh-1));
mark(cc_elem);
</script>

<P><INPUT TYPE='text' NAME='textfield1' ID='textfield1' style="font-size:16;color:blue" VALUE=" your scrolltext here! for icons use $1, $2, ..." SIZE=40>
<button id='btn_sendtext'><b>Submit Text</b></button></p>
<hr />

<p><button id='btn_fill'>Fill</button> <button id='btn_clear'>Clear</button> <button id='btn_smiley'>Smiley</button> <button id='btn_pumpkin'>Pumpkin</button> <button id='btn_skull'>Skull</button> <button id='btn_heart'>Heart</button> <button id='btn_checker'>Checker</button></p>
<p><label id='iconlabel' for="icon">Icon 1:</label>
   <input id='slider_icon' type='range' min='1' max='10' step='1' value='1' style='width:220px;' onchange='set_buttoncaption(slider_icon.value)'/> </p>

<script>
function ps_click(e) { if(e.target.style.background==cc) e.target.style.background='rgb(0,0,0)'; else e.target.style.background=cc; }
w('<table border=1 style=\"border-collapse: separate; border-spacing: 2px;\">');
idx=0;
for(i=0;i<NUM_ROWS;i++) {
 w('<tr>');
 for(j=0;j<NUM_COLUMNS;j++,idx++) {
  w('<td class=pixel-sel id=ps'+idx+'></td>');
  id('ps'+idx).addEventListener('click',ps_click);
 }
 w('</tr>');
}
w('</table>');
</script>
<p><input type='checkbox' id='cb_anim'>animate (go to next icon)</p> 
<p><button id='btn_copy' style='width:110px;' >Copy</button> <button id='btn_paste' style='width:110px;'>Paste</button>
   <button id='btn_submit' style='font-weight:bold'>Submit Icons</button></p>

<hr />
<table>
<!-- <tr><td>Text mode:</td><td><select id='select_temode'> <option value='1' selected='selected'>solid</option> <option value='2'>fade slow</option> <option value='3'>fade fast</option><option value='4'>blink slow</option><option value='5'>blink fast</option></select></td></tr>
-->
<tr><td>Text speed:</td> <td><input id='slider_tewait' type='range' style='height:45px; width:200px;' min='3' max='30' step='1' value='20' onchange='send_scwait(slider_tewait.value)'/></td></tr>
<tr><td>Text brightness:</td><td><input id='slider_tebright' type='range' style='height:45px; width:200px;' min='1' max='30' step='1' value='20' onchange='send_scbrightness(slider_tebright.value)'/></td></tr>
<tr><td>Icon anim speed:</td><td><input id='slider_icwait' type='range' style='height:45px; width:200px;' min='3' max='30' step='1' value='10' onchange='send_icwait(slider_icwait.value)'/></td></tr>
<tr><td>Icon brightness:</td><td><input id='slider_icbright' type='range' style='height:45px; width:200px;' min='1' max='30' step='1' value='23' onchange='send_icbrightness(slider_icbright.value)'/></td></tr>
<tr><td>Rainbow speed:</td><td><input id='slider_bgwait' type='range' style='height:45px; width:200px;' min='3' max='30' step='1' value='20' onchange='send_bgwait(slider_bgwait.value)'/></td></tr>
<tr><td>Background brightness:</td><td><input id='slider_bgbright' type='range' style='height:45px; width:200px;' min='1' max='30' step='1' value='8' onchange='send_bgbrightness(slider_bgbright.value)'/></td></tr>
</table>
<p><button id='btn_solid'>Unicolor Background</button> <button id='btn_rainbow'>Rainbow Background</button></p>
<hr />
<p><input type=checkbox id='cb_comm'>Show HTTP Get command</p>
<label id='lbl_comm'></label>

<script>
function Create2DArray() {
 var arr = [];
 for (var i=0;i<=MAX_ICONS+1;i++) 
 { arr[i] = []; for (var j=0;j<=ICON_PIXELS;j++) arr[i].push('000000'); }
 return arr;
}

var store=Create2DArray();
function get_icon(num)
{ for(i=0;i<ICON_PIXELS;i++) store[num][i]=rgb2cc(id('ps'+i).style.backgroundColor); 
  if(id('cb_anim').checked) store[num][ICON_PIXELS]='111111'; // store anim state in last pixel 
  else store[num][ICON_PIXELS]='000000';
}

function put_icon(num)
{ for(i=0;i<ICON_PIXELS;i++) id('ps'+i).style.backgroundColor=store[num][i]; 
  if(store[num][ICON_PIXELS]=='111111') id('cb_anim').checked=true; 
  else id('cb_anim').checked=false;
}

function rgb2cc(rgb) {
 if(!rgb) return '000000';
 rgb = rgb.match(/^rgba?\((\d+),\s*(\d+),\s*(\d+)(?:,\s*(\d+))?\)$/);
 function hex(x) { return ('0' + parseInt(x).toString(16)).slice(-2); }
 return '' + hex(rgb[1]) + hex(rgb[2]) + hex(rgb[3]);
}

id('btn_fill').addEventListener('click',function(e) {
 for(i=0;i<ICON_PIXELS;i++) id('ps'+i).style.background = cc;
});

id('btn_clear').addEventListener('click',function(e) {
 for(i=0;i<ICON_PIXELS;i++) id('ps'+i).style.background = 'rgb(0, 0, 0)';
});

function send_comm(comm) {
 var xhr=new XMLHttpRequest();
 xhr.onreadystatechange=function() {
  if(xhr.readyState==4 && xhr.status==200) {
  var jd=JSON.parse(xhr.responseText);
  }
 };
 comm = 'http://192.168.4.1'+comm;
 xhr.open('GET',comm,true);
 xhr.send();
}

function show_comm(comm) {
 comm = 'http://192.168.4.1'+comm;
 if(id('cb_comm').checked) id('lbl_comm').innerHTML=comm;
 else id('lbl_comm').innerHTML='';
}

id('btn_sendtext').addEventListener('click', function(e) {
 var comm='/sc?scrolltext='+document.getElementById('textfield1').value+'&color='+rgb2cc(cc)
 show_comm(comm);
 send_comm(comm);
});

id('btn_solid').addEventListener('click', function(e) {
 var comm='/bg?mode=0&color='+rgb2cc(cc);
 show_comm(comm);
 send_comm(comm);
});

id('btn_rainbow').addEventListener('click', function(e) {
 var comm='/bg?mode=1';
 show_comm(comm);
 send_comm(comm);
});

function callback(a){ 
 return function(){
  //console.log('send:"+a); 
  send_comm(a); 
}}

id('btn_submit').addEventListener('click', function(e) {
 var icon_num=id('slider_icon').value;
 get_icon(last_iconpos);
 for (num=1;num<=MAX_ICONS;num++) {
  var comm='/ic?icon='+num;
  if(store[num][ICON_PIXELS]=='111111') comm+='&anim=1'; else comm+='&anim=0';
  comm+='&pixels=';
  for(i=0;i<ICON_PIXELS;i++) comm+=store[num][i];
  setTimeout(callback(comm), 250*num);
 } 
});

id('btn_copy').addEventListener('click', function(e) {
 get_icon(MAX_ICONS+1);
});

id('btn_paste').addEventListener('click', function(e) {
 put_icon(MAX_ICONS+1);
});

function set_icon(icon, fg, bg) {
for(i=0;i<ICON_PIXELS;i++) id('ps'+i).style.background=(icon[i]>0)?fg:bg;
}

function set_icon2(icon) {
for(i=0;i<ICON_PIXELS;i++) id('ps'+i).style.background=icon[i];
}
id('btn_smiley').addEventListener('click', function(e) {
var smiley=[
0,1,1,1,0,
1,0,0,0,1,
1,1,0,1,1,
1,0,0,0,1,
1,1,1,1,1,
1,0,0,0,1,
0,1,1,1,0];
set_icon(smiley, '#00FF00', '#000000');
});

id('btn_heart').addEventListener('click', function(e) {
var heart=[
0,0,0,0,0,
0,1,0,1,0,
1,1,1,1,1,
1,1,1,1,1,
0,1,1,1,0,
0,0,1,0,0,
0,0,0,0,0];
set_icon(heart, '#FF0000', '#000020');
});

id('btn_checker').addEventListener('click', function(e) {
var checker=[
1,0,1,0,1,
0,1,0,1,0,
1,0,1,0,1,
0,1,0,1,0,
1,0,1,0,1,
0,1,0,1,0,
1,0,1,0,1];
set_icon(checker, '#FF0000', '#000020');
});

id('btn_skull').addEventListener('click', function(e) {
var skull=[
0,1,1,1,0,
1,0,0,0,1,
1,1,0,1,1,
1,0,0,0,1,
0,1,0,1,0,
0,1,0,1,0,
0,1,1,1,0];
set_icon(skull, '#0000FF', '#000000');
});

id('btn_pumpkin').addEventListener('click', function(e) {
var pumpkin=['#000000','#008000','#000000','#000000','#000000',
'#000000','#000000','#008000','#000000','#000000',
'#000000','#802000','#802000','#802000','#000000',
'#802000','#000000','#000000','#000000','#802000',
'#802000','#000000','#000000','#000000','#802000',
'#802000','#000000','#000000','#000000','#802000',
'#000000','#802000','#802000','#802000','#000000'];
set_icon2(pumpkin);
});

var last_iconpos = '1';

var xhr=new XMLHttpRequest();
function set_buttoncaption(text) {
 get_icon(last_iconpos);
 last_iconpos=text;
 id('iconlabel').textContent='Icon '+text+':';
 put_icon(text);
} 
function send_scbrightness(text) {
 // var e = id('select_temode');
 // var mode = e.options[e.selectedIndex].value;
 xhr.open('GET','http://192.168.4.1/sc?brightness='+text,true); // +'&mode='+mode,true);
 xhr.send();
} 
function send_scwait(text) {
 xhr.open('GET','http://192.168.4.1/sc?wait='+text,true);
 xhr.send();
} 
function send_bgwait(text) {
 xhr.open('GET','http://192.168.4.1/bg?wait='+text,true);
 xhr.send();
} 
function send_bgbrightness(text) {
 xhr.open('GET','http://192.168.4.1/bg?brightness='+text,true);
 xhr.send();
} 
function send_bgmode(text) {
 xhr.open('GET','http://192.168.4.1/bg?mode='+text,true);
 xhr.send();
} 
function send_icwait(text) {
 xhr.open('GET','http://192.168.4.1/ic?wait='+text,true);
 xhr.send();
} 
function send_icbrightness(text) {
 xhr.open('GET','http://192.168.4.1/ic?brightness='+text,true);
 xhr.send();
} 
function send_brightness(text) {
 xhr.open('GET','http://192.168.4.1/cc?brightness='+text,true);
 xhr.send();
} 
</script>
</body>
</html>
)";

