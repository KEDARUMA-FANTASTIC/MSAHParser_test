/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <Arduino.h>

#include "../src/mash_parser.hpp"

//#include <iostream>
//#include <array>
//#include <cstdlib>
//#include  <iomanip>
//#include <cassert>

#define HERE_DOC(...) #__VA_ARGS__ "\n";

namespace {

const char w3c_home_html[] PROGMEM = HERE_DOC(
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<!-- Generated from data/head-home.php, ../../smarty/{head.tpl} -->
<head>
<title>World Wide Web Consortium (W3C)</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="Help" href="/Help/" />
<link rel="stylesheet" href="/2008/site/css/minimum" type="text/css" media="all" />
<style type="text/css" media="print, screen and (min-width: 481px)">
</style>
<link href="/2008/site/css/minimum" rel="stylesheet" type="text/css" media="only screen and (max-width: 480px)" />
<meta name="viewport" content="width=device-width" />
<link rel="stylesheet" href="/2008/site/css/print" type="text/css" media="print" />
<link rel="shortcut icon" href="/2008/site/images/favicon.ico" type="image/x-icon" />
<meta name="description" content="The World Wide Web Consortium (W3C) is an international community where Member organizations, a full-time staff, and the public work together to develop Web standards." />
<link rel="alternate" type="application/atom+xml" title="W3C News" href="/blog/news/feed/atom" />
</head>
<body id="www-w3-org" class="w3c_public w3c_home">
<div id="w3c_container">
<!-- Generated from data/mast-home.php, ../../smarty/{mast.tpl} -->
<div id="w3c_mast"><!-- #w3c_mast / Page top header -->
<h1 class="logo"><a tabindex="2" accesskey="1" href="/"><img src="/2008/site/images/logo-w3c-mobile-lg" width="90" height="53" alt="W3C" /></a> <span class="alt-logo">W3C</span></h1>
</body>
</html>
);

const char w3c_xml_example_food_menu_xml[] PROGMEM = HERE_DOC(
<?xml version="1.0" encoding="UTF-8"?>
<breakfast_menu>
  <food>
    <name>Belgian Waffles</name>
    <price>$5.95</price>
    <description>Two of our famous Belgian Waffles with plenty of real maple syrup</description>
    <calories>650</calories>
  </food>
  <food>
    <name>Strawberry Belgian Waffles</name>
    <price>$7.95</price>
    <description>Light Belgian waffles covered with strawberries and whipped cream</description>
    <calories>900</calories>
  </food>
  <food>
    <name>Berry-Berry Belgian Waffles</name>
    <price>$8.95</price>
    <description>Light Belgian waffles covered with an assortment of fresh berries and whipped cream</description>
    <calories>900</calories>
  </food>
  <food>
    <name>French Toast</name>
    <price>$4.50</price>
    <description>Thick slices made from our homemade sourdough bread</description>
    <calories>600</calories>
  </food>
  <food>
    <name>Homestyle Breakfast</name>
    <price>$6.95</price>
    <description>Two eggs, bacon or sausage, toast, and our ever-popular hash browns</description>
    <calories>950</calories>
  </food>
</breakfast_menu>
);

void concat_str(String& str, const char* cstr_to_add, uint16_t count) {
    for (int i = 0; i < count && cstr_to_add[i]; i ++) {
        str.concat(cstr_to_add[i]);
    }
}

void parser_handler(uint32_t element_count, const char* element_name, uint16_t element_name_length, const char* part_of_value, uint16_t part_of_value_length)
{
    String elem_name_str;
    concat_str(elem_name_str, element_name, element_name_length);

    String part_value_str;
    concat_str(part_value_str, part_of_value, part_of_value_length);

    // count:###1, name:[###2]:###3, value:{###4}:###5
    // ###1 - Number of elements found
    // ###2 - Element found
    // ###3 - Length of found element
    // ###4 - Value
    // ###5 - Length of value
    // *The value will be output from the found element to the previous element
    Serial.print(F("count:"));
    Serial.print(element_count);

    Serial.print(F(", name:["));
    Serial.print(elem_name_str);
    Serial.print(F("]:"));
    Serial.print(element_name_length);

    Serial.print(F(", value:["));
    Serial.print(part_value_str);
    Serial.print(F("]:"));
    Serial.print(part_of_value_length);

    Serial.print(F("\n"));
}

} // namespace


void test_html_parse()
{
    MSAHParser parser(parser_handler);

    for (int i = 0; i != w3c_home_html[i]; i ++) {
        parser.write(w3c_home_html[i]);
    }
}

void test_xml_parse()
{
    MSAHParser parser(parser_handler);

    for (int i = 0; i != w3c_xml_example_food_menu_xml[i]; i ++) {
        parser.write(w3c_xml_example_food_menu_xml[i]);
    }
}

void setup() {
    delay(2000);

    Serial.begin(9600);
    Serial.println("\n\n\nhello!!!");

    test_html_parse();
    test_xml_parse();
}


void loop() {
}
