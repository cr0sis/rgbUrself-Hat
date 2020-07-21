/*******************************************************************
    Connect to Twtich Chat with a Bot
   Created with code from TheOtherLoneStar (https://www.twitch.tv/theotherlonestar)
   and Brian Lough (https://www.twitch.tv/brianlough)
   Hackaday IO: https://hackaday.io/otherlonestar
   This hat script slapped together by cr0sis and barf:
   - (https://twitch.tv/cr0sis) 
   - (https://cr0s.is) 
   - (https://github.com/cr0sis)
   - barf (the pub)
   
 *******************************************************************/



#include <ESP8266WiFi.h>
#include <IRCClient.h>
#include <FastLED.h>
#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    66
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          45
#define FRAMES_PER_SECOND  120
#define IRC_SERVER   "irc.chat.twitch.tv"
#define IRC_PORT     6667
#define VOLTS            5
#define MAX_MA         500

uint8_t chosenDelay = 20;

int lastPatternChangeTime = 0;

char ssid[] = "*****";       // your network SSID (name)
char password[] = "*****";  // your network key

//The name of the channel that you want the bot to join
const String twitchChannelName = "cr0sis";

//The name that you want the bot to have
#define TWITCH_BOT_NAME "cr0sbot"

//OAuth Key for your twitch bot
// https://twitchapps.com/tmi/
#define TWITCH_OAUTH_TOKEN "oauth:928ph5dwv2wreb1du3b9orgpcfgyrt"

//------------------------------

String ircChannel = "";

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() {

  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS)
  .setCorrection(TypicalLEDStrip);
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
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current



void cycle()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
  if(millis() > (lastPatternChangeTime + (chosenDelay*1000))){
    Serial.println("running chosen routine");
    Serial.println(chosenDelay);
    nextPattern();  // change patterns periodically
    lastPatternChangeTime = millis();
  }
}


#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS - 1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16( i + 7, 0, NUM_LEDS - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
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
  client.loop();
  cycle();
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
   
    if (ircMessage.nick == "STREAMLABS" && ircMessage.text.indexOf("changed the delay:") > 0) {
      String newDelay = getValue(ircMessage.text, ':', 1);
      newDelay.trim();
      newDelay.toLowerCase();
      Serial.println(newDelay);
      if (newDelay == "+1") {
        chosenDelay -= 1;
        sendTwitchMessage("1s removed from delay.");
        Serial.println(chosenDelay);
        return;
      }
      if (newDelay == "-10") {
        chosenDelay -= 10;
        sendTwitchMessage("10s removed from delay.");
        Serial.println(chosenDelay);
        return;
      }
      if (newDelay == "+10") {
        chosenDelay += 10;
        sendTwitchMessage("10s added to delay.");
        Serial.println(chosenDelay);
        return;
      }
      if (newDelay == "slower") {
        chosenDelay += 1;
        sendTwitchMessage("1s added to delay.");
        Serial.println(chosenDelay);
        return;
      }
      if (newDelay == "next") {
        nextPattern();
        sendTwitchMessage("Delay bypassed. Delay = " + chosenDelay);
        return;
      }
      if (newDelay != "faster" or "slower" or "next") {
        sendTwitchMessage("You chose stupid, I took your points anyway. !commands for help");
        Serial.println(chosenDelay);
        return;
      } else {
        Serial.println("didnt floop hat");
      }
    }
    return;
    } else {
    Serial.println("wasn't a priv");
  }
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
