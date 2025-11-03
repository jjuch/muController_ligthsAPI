// API-functies voor de lichtshow
#include "lichtshow_hulpFuncties.h"

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
int lichtsterkte = 0;

int rood[]    = {255, 0, 0};
int oranje[]  = {255, 165, 0};
int geel[]    = {255, 255, 0};
int groen[]   = {0, 255, 0};
int blauw[]   = {0, 0, 255};
int wit[]     = {255, 255, 255};
int zwart[]   = {0, 0, 0};

// === API FUNCTIES ===

void meetLicht() {
  lichtsterkte = analogRead(LDR_PIN);
}

void wacht(int basisTijd) {
  meetLicht();
  int aangepasteTijd = map(lichtsterkte, 0, 4095, basisTijd * 2, basisTijd / 2);
  delay(aangepasteTijd);
}

void zetAlleLedsAan(int kleur[]) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(kleur[0], kleur[1], kleur[2]));
  }
  pixels.show();
}

void zetAlleLedsUit() {
  zetAlleLedsAan(zwart);
}

void zetLedAan(int leds[], int* kleuren[], int lengte) {
  for (int i = 0; i < lengte; i++) {
    pixels.setPixelColor(leds[i], pixels.Color(kleuren[i][0], kleuren[i][1], kleuren[i][2]));
  }
  pixels.show();
}

void roteerLeds(int n) {
  uint32_t huidigeKleuren[NUMPIXELS];

  for (int i = 0; i < NUMPIXELS; i++) {
    huidigeKleuren[i] = pixels.getPixelColor(i);
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor((i + n) % NUMPIXELS, huidigeKleuren[i]);
  }
  pixels.show();
}

void veranderHelderheid(int waarde) {
  pixels.setBrightness(constrain(waarde, 0, 255));
  pixels.show();
}

void herhaal(int aantalKeer, void (*functie)()) {
  for (int i = 0; i < aantalKeer; i++) {
    functie();
  }
}

void wisselKleuren(int leds[], int* kleuren1[], int* kleuren2[], int lengte) {
  zetLedAan(leds, kleuren1, lengte);
  wacht(300);
  zetLedAan(leds, kleuren2, lengte);
  wacht(300);
}

void lichtOp(int kleur[], int stappen, int snelheid) {
  for (int i = 0; i <= stappen; i++) {
    int r = kleur[0] * i / stappen;
    int g = kleur[1] * i / stappen;
    int b = kleur[2] * i / stappen;
    int nieuweKleur[] = {r, g, b};
    zetAlleLedsAan(nieuweKleur);
    delay(snelheid);
  }
}

void doof(int kleur[], int stappen, int snelheid) {
  for (int i = stappen; i >= 0; i--) {
    int r = kleur[0] * i / stappen;
    int g = kleur[1] * i / stappen;
    int b = kleur[2] * i / stappen;
    int nieuweKleur[] = {r, g, b};
    zetAlleLedsAan(nieuweKleur);
    delay(snelheid);
  }
}
