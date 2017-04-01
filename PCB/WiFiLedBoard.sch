<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="wirepad">
<description>&lt;b&gt;Single Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SMD1,27-2,54">
<description>&lt;b&gt;SMD PAD&lt;/b&gt;</description>
<smd name="1" x="0" y="0" dx="1.27" dy="2.54" layer="1"/>
<text x="0" y="0" size="0.0254" layer="27">&gt;VALUE</text>
<text x="-0.8" y="-2.4" size="1.27" layer="25" rot="R90">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="PAD">
<wire x1="-1.016" y1="1.016" x2="1.016" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SMD2" prefix="PAD" uservalue="yes">
<description>&lt;b&gt;SMD PAD&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SMD1,27-2,54">
<connects>
<connect gate="1" pin="P" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA03-1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-3.81" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-0.635" size="1.27" layer="21" ratio="10">1</text>
<text x="-3.81" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MA03-1">
<wire x1="3.81" y1="-5.08" x2="-1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="-1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<text x="-1.27" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA03-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MA03-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA03-1">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="PAD1" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD2" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD3" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD4" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD5" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD6" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD7" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD8" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD9" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD10" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD11" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD12" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD13" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD14" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD15" library="wirepad" deviceset="SMD2" device=""/>
<part name="SV1" library="con-lstb" deviceset="MA03-1" device=""/>
<part name="PAD16" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD17" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD18" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD19" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD20" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD21" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD22" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD23" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD24" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD25" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD26" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD27" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD28" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD29" library="wirepad" deviceset="SMD2" device=""/>
<part name="PAD30" library="wirepad" deviceset="SMD2" device=""/>
<part name="SV2" library="con-lstb" deviceset="MA03-1" device=""/>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND6" library="supply1" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="PAD1" gate="1" x="25.4" y="83.82" rot="R90"/>
<instance part="PAD2" gate="1" x="30.48" y="83.82" rot="R90"/>
<instance part="PAD3" gate="1" x="35.56" y="83.82" rot="R90"/>
<instance part="PAD4" gate="1" x="53.34" y="83.82" rot="R90"/>
<instance part="PAD5" gate="1" x="58.42" y="83.82" rot="R90"/>
<instance part="PAD6" gate="1" x="63.5" y="83.82" rot="R90"/>
<instance part="PAD7" gate="1" x="81.28" y="83.82" rot="R90"/>
<instance part="PAD8" gate="1" x="86.36" y="83.82" rot="R90"/>
<instance part="PAD9" gate="1" x="91.44" y="83.82" rot="R90"/>
<instance part="PAD10" gate="1" x="109.22" y="83.82" rot="R90"/>
<instance part="PAD11" gate="1" x="114.3" y="83.82" rot="R90"/>
<instance part="PAD12" gate="1" x="119.38" y="83.82" rot="R90"/>
<instance part="PAD13" gate="1" x="134.62" y="83.82" rot="R90"/>
<instance part="PAD14" gate="1" x="139.7" y="83.82" rot="R90"/>
<instance part="PAD15" gate="1" x="144.78" y="83.82" rot="R90"/>
<instance part="SV1" gate="G$1" x="162.56" y="88.9" rot="R180"/>
<instance part="PAD16" gate="1" x="25.4" y="58.42" rot="R90"/>
<instance part="PAD17" gate="1" x="30.48" y="58.42" rot="R90"/>
<instance part="PAD18" gate="1" x="35.56" y="58.42" rot="R90"/>
<instance part="PAD19" gate="1" x="53.34" y="58.42" rot="R90"/>
<instance part="PAD20" gate="1" x="58.42" y="58.42" rot="R90"/>
<instance part="PAD21" gate="1" x="63.5" y="58.42" rot="R90"/>
<instance part="PAD22" gate="1" x="81.28" y="58.42" rot="R90"/>
<instance part="PAD23" gate="1" x="86.36" y="58.42" rot="R90"/>
<instance part="PAD24" gate="1" x="91.44" y="58.42" rot="R90"/>
<instance part="PAD25" gate="1" x="109.22" y="58.42" rot="R90"/>
<instance part="PAD26" gate="1" x="114.3" y="58.42" rot="R90"/>
<instance part="PAD27" gate="1" x="119.38" y="58.42" rot="R90"/>
<instance part="PAD28" gate="1" x="134.62" y="58.42" rot="R90"/>
<instance part="PAD29" gate="1" x="139.7" y="58.42" rot="R90"/>
<instance part="PAD30" gate="1" x="144.78" y="58.42" rot="R90"/>
<instance part="SV2" gate="G$1" x="162.56" y="63.5" rot="R180"/>
<instance part="GND3" gate="1" x="127" y="76.2"/>
<instance part="GND4" gate="1" x="71.12" y="76.2"/>
<instance part="GND5" gate="1" x="127" y="50.8"/>
<instance part="GND6" gate="1" x="71.12" y="50.8"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="PAD3" gate="1" pin="P"/>
<wire x1="35.56" y1="86.36" x2="38.1" y2="88.9" width="0.1524" layer="91"/>
<wire x1="38.1" y1="88.9" x2="50.8" y2="88.9" width="0.1524" layer="91"/>
<pinref part="PAD4" gate="1" pin="P"/>
<wire x1="50.8" y1="88.9" x2="53.34" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="PAD2" gate="1" pin="P"/>
<wire x1="30.48" y1="86.36" x2="35.56" y2="91.44" width="0.1524" layer="91"/>
<wire x1="35.56" y1="91.44" x2="55.88" y2="91.44" width="0.1524" layer="91"/>
<pinref part="PAD5" gate="1" pin="P"/>
<wire x1="55.88" y1="91.44" x2="58.42" y2="88.9" width="0.1524" layer="91"/>
<wire x1="58.42" y1="88.9" x2="58.42" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="PAD9" gate="1" pin="P"/>
<wire x1="91.44" y1="86.36" x2="93.98" y2="88.9" width="0.1524" layer="91"/>
<wire x1="93.98" y1="88.9" x2="106.68" y2="88.9" width="0.1524" layer="91"/>
<pinref part="PAD10" gate="1" pin="P"/>
<wire x1="106.68" y1="88.9" x2="109.22" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="PAD8" gate="1" pin="P"/>
<wire x1="86.36" y1="86.36" x2="91.44" y2="91.44" width="0.1524" layer="91"/>
<wire x1="91.44" y1="91.44" x2="111.76" y2="91.44" width="0.1524" layer="91"/>
<pinref part="PAD11" gate="1" pin="P"/>
<wire x1="111.76" y1="91.44" x2="114.3" y2="88.9" width="0.1524" layer="91"/>
<wire x1="114.3" y1="88.9" x2="114.3" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="PAD18" gate="1" pin="P"/>
<wire x1="35.56" y1="60.96" x2="38.1" y2="63.5" width="0.1524" layer="91"/>
<wire x1="38.1" y1="63.5" x2="50.8" y2="63.5" width="0.1524" layer="91"/>
<pinref part="PAD19" gate="1" pin="P"/>
<wire x1="50.8" y1="63.5" x2="53.34" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="PAD17" gate="1" pin="P"/>
<wire x1="30.48" y1="60.96" x2="35.56" y2="66.04" width="0.1524" layer="91"/>
<wire x1="35.56" y1="66.04" x2="55.88" y2="66.04" width="0.1524" layer="91"/>
<pinref part="PAD20" gate="1" pin="P"/>
<wire x1="55.88" y1="66.04" x2="58.42" y2="63.5" width="0.1524" layer="91"/>
<wire x1="58.42" y1="63.5" x2="58.42" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="PAD24" gate="1" pin="P"/>
<wire x1="91.44" y1="60.96" x2="93.98" y2="63.5" width="0.1524" layer="91"/>
<wire x1="93.98" y1="63.5" x2="106.68" y2="63.5" width="0.1524" layer="91"/>
<pinref part="PAD25" gate="1" pin="P"/>
<wire x1="106.68" y1="63.5" x2="109.22" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="PAD23" gate="1" pin="P"/>
<wire x1="86.36" y1="60.96" x2="91.44" y2="66.04" width="0.1524" layer="91"/>
<wire x1="91.44" y1="66.04" x2="111.76" y2="66.04" width="0.1524" layer="91"/>
<pinref part="PAD26" gate="1" pin="P"/>
<wire x1="111.76" y1="66.04" x2="114.3" y2="63.5" width="0.1524" layer="91"/>
<wire x1="114.3" y1="63.5" x2="114.3" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="PAD14" gate="1" pin="P"/>
<wire x1="139.7" y1="86.36" x2="142.24" y2="88.9" width="0.1524" layer="91"/>
<pinref part="SV1" gate="G$1" pin="2"/>
<wire x1="142.24" y1="88.9" x2="154.94" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="PAD29" gate="1" pin="P"/>
<wire x1="139.7" y1="60.96" x2="142.24" y2="63.5" width="0.1524" layer="91"/>
<pinref part="SV2" gate="G$1" pin="2"/>
<wire x1="142.24" y1="63.5" x2="154.94" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="PAD30" gate="1" pin="P"/>
<pinref part="SV2" gate="G$1" pin="1"/>
<wire x1="144.78" y1="60.96" x2="149.86" y2="66.04" width="0.1524" layer="91"/>
<wire x1="149.86" y1="66.04" x2="154.94" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="PAD15" gate="1" pin="P"/>
<pinref part="SV1" gate="G$1" pin="3"/>
<wire x1="144.78" y1="86.36" x2="154.94" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="PAD13" gate="1" pin="P"/>
<pinref part="SV1" gate="G$1" pin="1"/>
<wire x1="134.62" y1="86.36" x2="139.7" y2="91.44" width="0.1524" layer="91"/>
<wire x1="139.7" y1="91.44" x2="154.94" y2="91.44" width="0.1524" layer="91"/>
<pinref part="PAD7" gate="1" pin="P"/>
<wire x1="81.28" y1="86.36" x2="88.9" y2="93.98" width="0.1524" layer="91"/>
<wire x1="88.9" y1="93.98" x2="116.84" y2="93.98" width="0.1524" layer="91"/>
<pinref part="PAD12" gate="1" pin="P"/>
<wire x1="116.84" y1="93.98" x2="119.38" y2="91.44" width="0.1524" layer="91"/>
<wire x1="119.38" y1="91.44" x2="119.38" y2="86.36" width="0.1524" layer="91"/>
<wire x1="134.62" y1="86.36" x2="127" y2="86.36" width="0.1524" layer="91"/>
<pinref part="PAD1" gate="1" pin="P"/>
<wire x1="127" y1="86.36" x2="119.38" y2="86.36" width="0.1524" layer="91"/>
<wire x1="25.4" y1="86.36" x2="33.02" y2="93.98" width="0.1524" layer="91"/>
<wire x1="33.02" y1="93.98" x2="58.42" y2="93.98" width="0.1524" layer="91"/>
<pinref part="PAD6" gate="1" pin="P"/>
<wire x1="58.42" y1="93.98" x2="63.5" y2="88.9" width="0.1524" layer="91"/>
<wire x1="63.5" y1="88.9" x2="63.5" y2="86.36" width="0.1524" layer="91"/>
<wire x1="81.28" y1="86.36" x2="71.12" y2="86.36" width="0.1524" layer="91"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="71.12" y1="86.36" x2="63.5" y2="86.36" width="0.1524" layer="91"/>
<wire x1="71.12" y1="78.74" x2="71.12" y2="86.36" width="0.1524" layer="91"/>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="127" y1="78.74" x2="127" y2="86.36" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="PAD22" gate="1" pin="P"/>
<wire x1="81.28" y1="60.96" x2="88.9" y2="68.58" width="0.1524" layer="91"/>
<wire x1="88.9" y1="68.58" x2="116.84" y2="68.58" width="0.1524" layer="91"/>
<pinref part="PAD27" gate="1" pin="P"/>
<wire x1="116.84" y1="68.58" x2="119.38" y2="66.04" width="0.1524" layer="91"/>
<wire x1="119.38" y1="66.04" x2="119.38" y2="60.96" width="0.1524" layer="91"/>
<pinref part="SV2" gate="G$1" pin="3"/>
<wire x1="154.94" y1="60.96" x2="149.86" y2="60.96" width="0.1524" layer="91"/>
<wire x1="149.86" y1="60.96" x2="144.78" y2="66.04" width="0.1524" layer="91"/>
<wire x1="144.78" y1="66.04" x2="137.16" y2="66.04" width="0.1524" layer="91"/>
<pinref part="PAD28" gate="1" pin="P"/>
<wire x1="137.16" y1="66.04" x2="134.62" y2="63.5" width="0.1524" layer="91"/>
<wire x1="134.62" y1="63.5" x2="134.62" y2="60.96" width="0.1524" layer="91"/>
<wire x1="119.38" y1="60.96" x2="127" y2="60.96" width="0.1524" layer="91"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="127" y1="60.96" x2="134.62" y2="60.96" width="0.1524" layer="91"/>
<wire x1="127" y1="53.34" x2="127" y2="60.96" width="0.1524" layer="91"/>
<pinref part="PAD16" gate="1" pin="P"/>
<wire x1="25.4" y1="60.96" x2="33.02" y2="68.58" width="0.1524" layer="91"/>
<wire x1="33.02" y1="68.58" x2="58.42" y2="68.58" width="0.1524" layer="91"/>
<pinref part="PAD21" gate="1" pin="P"/>
<wire x1="58.42" y1="68.58" x2="63.5" y2="63.5" width="0.1524" layer="91"/>
<wire x1="63.5" y1="63.5" x2="63.5" y2="60.96" width="0.1524" layer="91"/>
<wire x1="63.5" y1="60.96" x2="71.12" y2="60.96" width="0.1524" layer="91"/>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="71.12" y1="60.96" x2="81.28" y2="60.96" width="0.1524" layer="91"/>
<wire x1="71.12" y1="53.34" x2="71.12" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
