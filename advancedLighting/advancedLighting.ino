#include <Adafruit_NeoPixel.h>

#define LED_PIN     0       // GPIO0 connected to NeoPixel ring
#define BUTTON_PIN  9       // GPIO9 is BOOT button on ESP32-C3
#define NUMPIXELS   12

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Effect index
int currentEffect = 0;
const int numEffects = 4;

// Debounce
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // BOOT button is active LOW
  randomSeed(analogRead(0));
}

void loop() {
  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    currentEffect = (currentEffect + 1) % numEffects;
    lastDebounceTime = millis();
  }

  // Run current effect
  switch (currentEffect) {
    case 0: randomColors(); break;
    case 1: rainbowCycle(); break;
    case 2: theaterChase(); break;
    case 3: colorWipe(); break;
  }
}

// === EFFECT FUNCTIONS ===

void randomColors() {
  Serial.println("Random Colors");
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(random(256), random(256), random(256)));
  }
  pixels.show();
  delay(500);
}

void rainbowCycle() {
  Serial.println("Rainbow");
  static uint16_t j = 0;
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, Wheel((i * 256 / NUMPIXELS + j) & 255));
  }
  pixels.show();
  j++;
  delay(20);
}

void theaterChase() {
  static int q = 0;
  for (int i = 0; i < NUMPIXELS; i++) {
    if ((i + q) % 3 == 0) {
      pixels.setPixelColor(i, pixels.Color(127, 0, 127)); // Purple
    } else {
      pixels.setPixelColor(i, 0); // Off
    }
  }
  pixels.show();
  q = (q + 1) % 3;
  delay(100);
}

void colorWipe() {
  Serial.println("Wipe Clean");
  static int numberOfColors = 3;
  static int i = 0;
  static int j = 0;
  switch (j) {
    case 0: pixels.setPixelColor(i, pixels.Color(0, 255, 0)); break; // Green
    case 1: pixels.setPixelColor(i, pixels.Color(255, 0, 0)); break; // Red
    case 2: pixels.setPixelColor(i, pixels.Color(0, 0, 255)); break; // Blue
  }
  // pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Green
  pixels.show();
  i = (i + 1) % NUMPIXELS;
  if (i == 0) {
    j = (j + 1) % numberOfColors;
  }
  delay(100);
}

// === HELPER ===

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
