// Wemost example http://www.esp8266learning.com/wemos-mini-ws2812b-example.php
#include <Adafruit_NeoPixel.h>
#define PIN D2
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setupRGB() {
  pixels.begin();
}

unsigned short bright = 8;
void setWhite() {
  pixels.setPixelColor(0, pixels.Color(bright, bright, bright++));
  pixels.show();
}
void setR() {
  pixels.setPixelColor(0, pixels.Color(bright++,0,0));
  pixels.show();
}
void setG() {
  pixels.setPixelColor(0, pixels.Color(0, bright++,0));
  pixels.show();
}
void setB() {
  pixels.setPixelColor(0, pixels.Color(0,0,bright++));
  pixels.show();
}

// Not used (yet :) )
void rgbLED()
{
 int delayval = 500; // delay for half a second
 // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

 for(int i=0;i<NUMPIXELS;i++)
 {
   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
   pixels.setPixelColor(i, pixels.Color(0,255,0));
   pixels.show();
   delay(delayval);
   pixels.setPixelColor(i, pixels.Color(255,0,0));
   pixels.show();
   delay(delayval);
   pixels.setPixelColor(i, pixels.Color(0,0,255));
   pixels.show();
   delay(delayval);
 }
}
