/*******************************************************************
   Connect to Twtich Chat with a Bot
   Created with code from TheOtherLoneStar (https://www.twitch.tv/theotherlonestar)
   and https://github.com/fredimachado/ArduinoIRC
   By cr0sis (https://cr0s.is) (https://github.com/cr0sis)
 *******************************************************************/

#include <ESP8266WiFi.h>          
#include <IRCClient.h>
#include <FastLED.h>
#define NUM_LEDS 19
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
//define your default values here, if there are different values in config.json, they are overwritten.

#define IRC_SERVER   "irc.chat.twitch.tv"
#define IRC_PORT     6667

//------- Replace the following! ------
char ssid[] = "*********";       // your network SSID (name)
char password[] = "*******";  // your network key

//The name of the channel that you want the bot to join
const String twitchChannelName = "cr0sis";

//The name that you want the bot to have
#define TWITCH_BOT_NAME "cr0sbot"

//OAuth Key for your twitch bot
// https://twitchapps.com/tmi/
#define TWITCH_OAUTH_TOKEN "*****"

//------------------------------

String ircChannel = "";

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

// put your setup code here, to run once:
void setup() {

  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);

  Serial.println();

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ircChannel = "#" + twitchChannelName;

  client.setCallback(callback);
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
  
  // Try to connect to chat. If it loses connection try again
  if (!client.connected()) {
    Serial.println("Attempting to connect to " + ircChannel );
    // Attempt to connect
    // Second param is not needed by Twtich
    if (client.connect(TWITCH_BOT_NAME, "", TWITCH_OAUTH_TOKEN)) {
      client.sendRaw("JOIN " + ircChannel);
      Serial.println("connected and ready to rock");
      sendTwitchMessage("Ready to go Boss!");
      
    } else {
      Serial.println("failed... try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    return;
  }
  rainbow();
  client.loop();
  
}

void sendTwitchMessage(String message) {
  client.sendMessage(ircChannel, message);
}


void callback(IRCMessage ircMessage) {
  //Serial.println("In CallBack");

  if (ircMessage.command == "PRIVMSG" && ircMessage.text[0] != '\001') {
    //Serial.println("Passed private message.");
    ircMessage.nick.toUpperCase();

    String message("<" + ircMessage.nick + "> " + ircMessage.text);

    //prints chat to serial
    Serial.println(message);

    return;
  }
}
