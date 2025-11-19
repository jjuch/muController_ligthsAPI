#include "lichtshow_hulpfuncties.h"

// NIEUWE GLOBALE VARIABELEN
// Effect index
int huidigEffect = 0;
const int aantalEffecten = 4;

// DECLARATIE ALS DE KNOP GEBRUIKT WORDT
// Debounce
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(LDR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // BOOT button is active LOW
  pinMode(LED_BUILT_IN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    huidigEffect = (huidigEffect + 1) % aantalEffecten;
    lastDebounceTime = millis();
  }

  switch (huidigEffect) {
    case 0: 
      blink(geel);
      break;
    case 1: 
      regenboog(); 
      herhaal(NUMPIXELS, regenboogRotatie); 
      break;
    case 2: 
      willekeurig(); 
      break;
    case 3: 
      veegEffect(); 
      break;
  }
  effectDebugger(huidigEffect);
}

void blink(int kleur[]){
    zetAlleLedsAan(kleur);
    wacht(300);
    zetAlleLedsUit();
    wacht(300);
}

void willekeurig(){
  for (int i = 0; i < NUMPIXELS; i++) {
    int kleur[3] = {random(256), random(256), random(256)};
    int leds[1] = {i};
    int* kleuren[1] = {kleur};
    zetLedAan(leds, kleuren, 1);
  }
  wacht(300);
}

void veegEffect() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int leds[1] = {i};
    int* kleuren[1] = {blauw};
    zetLedAan(leds, kleuren, 1);
    wacht(100);
  }
  zetAlleLedsUit();
}

void regenboog() {
  int* kleuren[5] = {rood, oranje, geel, groen, blauw};
  for (int i = 0; i < NUMPIXELS; i++) {
    int leds[1] = {i};
    int* kleur[] = {kleuren[i % 5]};
    zetLedAan(leds, kleur, 1);
  }
}

void regenboogRotatie() {
  roteerLeds(1);
  wacht(300);
}
