#include <Wire.h>

#define SLAVE_ADDRESS 8 



const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pins for segments A-G
const int digitPins[] = {9, 10, 11, 12}; // Pins for digits 1-4
const int buzzerPin = 13; // Pin for the buzzer

const int digitPatterns[] = {
  0b11111100, 
  0b01100000, 
  0b11011010, 
  0b11110010, 
  0b01100110, 
  0b10110110, 
  0b10111110, 
  0b11100000, 
  0b11111110, 
  0b11110110  
};

int hours = 12;
int minutes = 0;
int alarmHours = 12;
int alarmMinutes = 1; // Set alarm time here
unsigned long lastUpdateTime = 0;
bool alarmTriggered = false;
bool alarmActive = false;
unsigned long alarmStartTime = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS); // Initialize I2C as slave
  Wire.onReceive(receiveEvent); // Register receive event
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastUpdateTime >= 60000) { // Check every minute
    updateTime();
    lastUpdateTime = currentTime;
  }
  
  displayTime();
  
  if (alarmTriggered) {
    if (!alarmActive) {
      triggerAlarm();
      alarmActive = true;
      alarmStartTime = currentTime;
    }
    if (currentTime - alarmStartTime >= 5000) { // Stop alarm after 5 seconds
      noTone(buzzerPin);
      alarmTriggered = false;
      alarmActive = false;
    }
  }
}

void displayTime() {
  int displayDigits[4] = {hours / 10, hours % 10, minutes / 10, minutes % 10};
  
  for (int digit = 0; digit < 4; digit++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(digitPins[i], HIGH);
    }
    
    for (int segment = 0; segment < 7; segment++) {
      digitalWrite(segmentPins[segment], bitRead(digitPatterns[displayDigits[digit]], 7 - segment));
    }
    
    digitalWrite(digitPins[digit], LOW);
    
    delayMicroseconds(2000);
  }
}

void updateTime() {
  minutes++;
  if (minutes == 60) {
    minutes = 0;
    hours++;
    if (hours == 24) {
      hours = 0;
    }
  }
  
  if (hours == alarmHours && minutes == alarmMinutes) {
    alarmTriggered = true;
  }
}

void triggerAlarm() {
  tone(buzzerPin, 1000, 500); // 1000 Hz tone for 500 ms
  delay(500);
  tone(buzzerPin, 1000, 500); // 1000 Hz tone for 500 ms
  delay(500);
  tone(buzzerPin, 1000, 500); // 1000 Hz tone for 500 ms
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    char c = Wire.read(); // Receive byte as a character
    Serial.write(c);
  }
}
