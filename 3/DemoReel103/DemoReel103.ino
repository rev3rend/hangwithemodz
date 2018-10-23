#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

// Params for width and height
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 8;
// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = false;
#define NUM_LEDS    kMatrixWidth*kMatrixHeight
CRGB leds[NUM_LEDS];



#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

int x, y, v;
int h = 0;
int s = 255;
  

void setup() {
  delay(3000); // 3 second delay for recovery

  Serial.begin(9600); // turns on the serial - 9600 is the baud rate

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  // SERIAL IN FROM COMPUTER TO ARDUINO:
  if (Serial.available()) {
     // look for the next valid integer in the incoming serial stream:
    x = Serial.parseInt();
    // do it again:
    y = Serial.parseInt();
    // do it again:
    v = Serial.parseInt();
    if (Serial.read() == '\n') {
      leds[XY(x, y)] = CHSV(h, s, v);
     Serial.println("got it!");
    }
  }

    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(v);

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  
  return i;
}

