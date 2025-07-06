#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ultrasonic pins
const int trigEntry = 2;
const int echoEntry = 3;
const int trigExit = 4;
const int echoExit = 5;

// Buzzer
const int buzzerPin = 6;

int totalSlots = 5;
int occupied = 0;

void setup() {
  pinMode(trigEntry, OUTPUT);
  pinMode(echoEntry, INPUT);
  pinMode(trigExit, OUTPUT);
  pinMode(echoExit, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Smart Parking System");
  display.display();
  delay(2000);
}

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout at 30ms
  long distance = duration * 0.034 / 2;
  return distance;
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Total Slots: ");
  display.println(totalSlots);
  display.print("Occupied: ");
  display.println(occupied);
  display.print("Available: ");
  display.println(totalSlots - occupied);

  if (occupied >= totalSlots) {
    display.setCursor(0, 50);
    display.setTextSize(1);
    display.println("PARKING FULL!");
    tone(buzzerPin, 1000); // Buzzer ON
  } else {
    noTone(buzzerPin); // Buzzer OFF
  }

  display.display();
}

void loop() {
  long entryDist = readDistance(trigEntry, echoEntry);
  long exitDist = readDistance(trigExit, echoExit);

  // Entry detected
  if (entryDist > 2 && entryDist < 10 && occupied < totalSlots) {
    occupied++;
    updateDisplay();
    delay(2000); // debounce
  }

  // Exit detected
  if (exitDist > 2 && exitDist < 10 && occupied > 0) {
    occupied--;
    updateDisplay();
    delay(2000); // debounce
  }

  updateDisplay();
  delay(500);
}