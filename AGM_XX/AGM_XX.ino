#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "defines.h"
#include "ctrl_functions.h"
#include "oled_display_functions.h"


void setup()
{
  WiFi.mode(WIFI_OFF);
  Wire.begin();
  pinsSetup();
  displaySetup();
}



void loop()
{
  
  stagingLoop();

  bat_operating();

}
