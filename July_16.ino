#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define LED_PIN 6
#define LED_COUNT 10

DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
   
  strip.begin();
  strip.show();
  strip.setBrightness(155);
}

void loop() {
  delay(1000); 
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(temp);
  Serial.print(F("ºC "));
  int colorTemp = map(temp, 20, 35, 0, 65536);
  for (int i=0; i<LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(colorTemp)));
    strip.show();
  }
  

}
