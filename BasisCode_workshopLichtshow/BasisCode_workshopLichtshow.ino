#include "lichtshow_hulpfuncties.h"

void setup() {
  
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(LDR_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  // Meet de lichtsterkte
  meetLicht();

  // Zet alle LEDs op blauw
  zetAlleLedsAan(blauw);
  wacht(1000);

  // Doe alle LEDs uit
  zetAlleLedsUit();
  wacht(1000);

  // Zet enkele LEDs aan met verschillende kleuren
  int leds[] = {0, 3, 6};
  int* kleuren[] = {rood, groen, blauw};
  zetLedAan(leds, kleuren, 3);
  wacht(1000);
  herhaal(50, lichtjesRoteren);
  
                               
  //veranderHelderheid(map(lichtsterkte, 0, 4095, 10, 255));
  lichtOp(rood, 20, 100);
  doof(rood, 20, 100);
}

void lichtjesRoteren(){
    roteerLeds(2);
    wacht(100);
}
