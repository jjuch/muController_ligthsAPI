#ifndef LICHTSHOW_HULPFUNCTIES_H
#define LICHTSHOW_HULPFUNCTIES_H

#include <Adafruit_NeoPixel.h>


// Hardware instellingen
#define LED_PIN     0
#define NUMPIXELS   12
#define LDR_PIN     1
#define BUTTON_PIN  9       // GPIO9 is BOOT button on ESP32-C3

// Externe variabelen
extern Adafruit_NeoPixel pixels;
extern int lichtsterkte;

extern int rood[];
extern int oranje[];
extern int geel[];
extern int blauw[];
extern int groen[];
extern int wit[];
extern int zwart[];


// Functiedeclaraties
void meetLicht();
void wacht(int basisTijd);
void zetAlleLedsAan(int kleur[]);
void zetAlleLedsUit();
void zetLedAan(int leds[], int* kleuren[], int lengte);
void roteerLeds(int n);
void veranderHelderheid(int waarde);
void herhaal(int aantalKeer, void (*functie)());
void wisselKleuren(int leds[], int* kleuren1[], int* kleuren2[], int lengte);
void lichtOp(int kleur[], int stappen, int snelheid);
void doof(int kleur[], int stappen, int snelheid);

#endif
