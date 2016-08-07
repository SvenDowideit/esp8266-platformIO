#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Wemost example http://www.esp8266learning.com/wemos-mini-ws2812b-example.php
#include <Adafruit_NeoPixel.h>
#define PIN D2
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);



// from https://github.com/platformio/platformio-examples/tree/develop/espressif/esp8266-webserver

const char* ssid = "0722";
const char* password = "Davisct440";
MDNSResponder mdns;

ESP8266WebServer server(80);

const int led = LED_BUILTIN;

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

void handleRoot() {
  pixels.setPixelColor(0, pixels.Color(255,0,0));
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  pixels.setPixelColor(0, pixels.Color(0,255,0));
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pixels.begin();

  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  pixels.setPixelColor(0, pixels.Color(0,0,255));
}

void loop(void){
  server.handleClient();
}
