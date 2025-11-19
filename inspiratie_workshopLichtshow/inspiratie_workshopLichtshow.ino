#include "lichtshow_hulpfuncties.h"

// NIEUWE GLOBALE VARIABELEN
// Effect index
int huidigEffect = 0;
int effectVeranderd = 1;
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
  digitalWrite(LED_BUILT_IN, HIGH);
  Serial.begin(115200);

  // Dit zorgt er voor dat de knop heel de tijd gemonitord wordt
  xTaskCreate(
    monitorKnop,    // Taak
    "monitorKnop",  // Naam
    2048,           // Stack Size
    NULL,           // Argumenten voor de taak
    1,              // Prioriteit
    NULL            // Task handle
    );

  // Dit zorgt er voor dat we het met behulp van het lichtje kunnen zien, welk effect er bezig is.
  xTaskCreate(
    effectDebugger,     // Taak
    "effectDebugger",   // Naam
    2048,               // Stack Size
    NULL,               // Argumenten voor de taak
    2,                  // Prioriteit
    NULL                // Task handle
    );
}

void loop() {
  switch (huidigEffect) {
    case 0: 
      blink(geel);
      break;
    case 1:
      if (effectVeranderd) { 
        regenboog(); 
        effectVeranderd = 0;
      } else {
        regenboogRotatie();
      }
      break;
    case 2: 
      willekeurig(); 
      break;
    case 3: 
      veegEffect(); 
      break;
  }
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

void monitorKnop(void *parameter) {
  // Check button press
  while(true) {
    if (digitalRead(BUTTON_PIN) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
      huidigEffect = (huidigEffect + 1) % aantalEffecten;
      effectVeranderd = 1;
      lastDebounceTime = millis();
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void effectDebugger(void *parameter) {
  while(true) {
    herhaal(huidigEffect + 1, blink_builtin_helper);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
