#include <FastLED.h>
#include "ESP_Wahaj.h"
#define NUM_LEDS 19
#define DATA_PIN 1
CRGB leds[NUM_LEDS];
String path = "nothing";
int pwm = 255;


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  start("TALKTALK80D321","******);  // Wifi details connect to
}


void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(195);
  }
}


void rainbow() {
  static uint8_t hue = 0;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 125);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    FastLED.delay(30);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 125);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    FastLED.delay(30);
  }
}


void loop() {
  //waitUntilNewReq();  //Waits until a new request from python come
  rainbow();
  if (CheckNewReq() == 1)
  {
    //Serial.println("new request");
    if (getPath() == "/blue") {
      returnThisStr("blue replied");
    }
    else if (getPath() == "/purple") {
      returnThisStr("purple replied");
    }
    else if (getPath() == "/favicon.ico") { //this happens for browsers only.
      returnThisStr("garbage");
    }

    else        //here we receive data. You can receive pwm255 and the decode it to 255 and also get more variables like this
    {
      path = getPath();
      Serial.println(path);   //String
      //returnThisStr("nothing");
      path.remove(0, 1);   //Remove slash /
      Serial.println(path);
      pwm = path.toInt();    //convert to int you can use toFloat()
      Serial.println(pwm);
    }
  }
}
