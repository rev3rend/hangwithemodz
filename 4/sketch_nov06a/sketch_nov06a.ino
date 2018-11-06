#include "FastLED.h"
#define NUM_LEDS 72 // # of LEDS in the strip
CRGB leds[NUM_LEDS];
#define PIN 3 // Output Pin to Data Line on Strip
#define COLOR_ORDER GRB  // I had to change this for my strip if your color is off then you know.
int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0; 

String foo = "";
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

void setup()
{
  Serial.begin(9600); 
  FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUM_LEDS);
}


void loop() { 

  int LEDno = 0;
  int ledR = 0;
  int ledG = 0;
  int ledB = 0;

  if(Serial.available()>0) // HEY! GOT ANY DATA?!
  {
    foo = Serial.readStringUntil('\n');
    pos1 = foo.indexOf(" ");
    val1 = foo.substring(0, pos1).toInt();
    pos2 = foo.indexOf(" ", pos1+1);
    val2 = foo.substring(pos1+1, pos2).toInt();
    pos3 = foo.indexOf(" ", pos2+1);
    val3 = foo.substring(pos2+1, pos3).toInt();
    pos4 = foo.indexOf("\n", pos3+1);
    val4 = foo.substring(pos3+1, pos4).toInt();

    LEDno = val1;
    ledR = val2;
    ledG = val3;
    ledB = val4;

    Serial.print(LEDno);
    Serial.print(" ");
    Serial.print(ledR);
    Serial.print(" ");
    Serial.print(ledG);
    Serial.print(" ");
    Serial.println(ledB);

    leds[LEDno].setRGB( ledR, ledG, ledB);
  }

    FastLED.setBrightness(100);
    FastLED.show();

}

