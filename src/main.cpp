
#include "wemos/wemos.h"
// Each of these is optional for the wemos target
#include "wemos/oled.h"
#include "wemos/rgbled.h"

#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>


// from https://github.com/platformio/platformio-examples/tree/develop/espressif/esp8266-webserver

const char* ssid = "0722";
const char* password = "Davisct440";

ESP8266WebServer server(80);

// The single colour LED on the CPU board
const int led = LED_BUILTIN;

void handleRoot() {
  setG();
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
  Serial.printf("OK\n");
}

void handleNotFound(){
  setR();
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
  Serial.printf("404\n");
}

void setup(void){
  setupRGB();

  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  Serial.begin(115200);

  setupWIFI(ssid, password);

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  setB();
  Serial.println("blue");
  // Disabling OLED as its breaking RGB - and its not as important to me yet
  //setupOLED();
  //Serial.println("OLED done");
  setWhite();
  Serial.println("ready");

}

void loop(void){
  updateWIFI();
  server.handleClient();
}
