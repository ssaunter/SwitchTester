#include <FastLED.h>

#define NUM_LEDS      5
#define DATA_PIN      D5
#define MODE_SWITCH   D6

const int buttonPins[NUM_LEDS] = {D0, D1, D2, D3, D4}; 

CRGB leds[NUM_LEDS];

const CRGB switchColors[NUM_LEDS] = {
  CRGB(30, 30, 30),    //Black 
  CRGB::Red,           //Red
  CRGB(200, 200, 255), //Silver 
  CRGB::Blue,          //Blue
  CRGB(139, 69, 19)    //Brown 
};

//LED Reactive Mode
unsigned long lightTimers[NUM_LEDS] = {0, 0, 0, 0, 0};
const int LIGHT_DURATION = 1000; //One second fade

void setup() {
  pinMode(MODE_SWITCH, INPUT_PULLUP);

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100); //LED strength 0 - 255
}

void loop() {
  bool isAlwaysOnMode = (digitalRead(MODE_SWITCH) == LOW); //Read slider switch
  unsigned long currentTime = millis();

  for (int i = 0; i < NUM_LEDS; i++) {
    
    bool isPressed = (digitalRead(buttonPins[i]) == LOW); //Low = pressed

    if (isPressed) {
      lightTimers[i] = currentTime;
    }

    if (isAlwaysOnMode) {
      leds[i] = switchColors[i];
    } 
    else {
      if (currentTime - lightTimers[i] < LIGHT_DURATION) {
        leds[i] = switchColors[i]; 
      } else {
        leds[i] = CRGB::Black;     
      }
    }
  }

  FastLED.show();
  
    delay(10); 
}