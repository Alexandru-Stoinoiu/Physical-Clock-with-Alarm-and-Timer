#include <Wire.h>

#define SLAVE_ADDRESS 8

const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pins for segments A-G
const int digitPins[] = {9, 10, 11, 12}; // Pins for digits 1-4
const int buzzerPin = 13; // Pin for the buzzer

const int digitPatterns[] = {
  0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
  0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110
};

int hours = 12;
int minutes = 0;
int alarmHours = 0;
int alarmMinutes = 0;
unsigned long lastUpdateTime = 0;
bool alarmTriggered = false;
bool alarmActive = false;
unsigned long alarmStartTime = 0;
int mode = 0; // 0 - Clock, 1 - Timer

int realHours = 12;
int realMinutes = 0;
unsigned long lastRealTimeUpdate = 0;

int timerHours = 0;
int timerMinutes = 0;
unsigned long timerStartTime = 0;
bool timerRunning = false;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastRealTimeUpdate >= 60000) {
    updateRealTime();
    lastRealTimeUpdate = currentTime;
  }
  
  if (mode == 0) {
    hours = realHours;
    minutes = realMinutes;
    displayTime();
  } else if (mode == 1) {
    updateAndDisplayTimer();
  }
  
  checkAlarm();
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

void updateRealTime() {
  realMinutes++;
  if (realMinutes == 60) {
    realMinutes = 0;
    realHours = (realHours + 1) % 24;
  }
  
  if (realHours == alarmHours && realMinutes == alarmMinutes) {
    alarmTriggered = true;
  }
}

void updateAndDisplayTimer() {
  if (timerRunning) {
    unsigned long elapsedSeconds = (millis() - timerStartTime) / 1000;
    int remainingSeconds = (timerHours * 3600 + timerMinutes * 60) - elapsedSeconds;
    
    if (remainingSeconds <= 0) {
      timerRunning = false;
      alarmTriggered = true;
      mode = 0; // Switch back to clock mode
    } else {
      hours = remainingSeconds / 3600;
      minutes = (remainingSeconds % 3600) / 60;
      displayTime();
    }
  } else {
    hours = timerHours;
    minutes = timerMinutes;
    displayTime();
  }
}

void checkAlarm() {
  if (alarmTriggered) {
    if (!alarmActive) {
      alarmActive = true;
    }
    tone(buzzerPin, 1000); // Continuous tone
  }
}


void stopAlarm() {
  alarmTriggered = false;
  alarmActive = false;
  noTone(buzzerPin);
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    char command[6];
    int i = 0;
    while (Wire.available() && i < 5) {
      command[i++] = Wire.read();
    }
    command[i] = '\0';
    
    if (strcmp(command, "Clock") == 0) {
      mode = 0;
      hours = realHours;
      minutes = realMinutes;
    } else if (strcmp(command, "Alarm") == 0) {
      mode = 0;
      if (Wire.available() >= 2) {
        alarmHours = Wire.read();
        alarmMinutes = Wire.read();
        Serial.println("Alarm set to:");
        Serial.print(alarmHours);
        Serial.print(" : ");
        Serial.print(alarmMinutes);
      }
    } else if (strcmp(command, "Timer") == 0) {
      mode = 1;
      if (Wire.available() >= 2) {
        timerHours = Wire.read();
        timerMinutes = Wire.read();
        timerStartTime = millis();
        timerRunning = true;
        Serial.println("Timer set to:");
        Serial.print(timerHours);
        Serial.print(" : ");
        Serial.print(timerMinutes);
      }
    } else if (strcmp(command, "StopA") == 0) {
      stopAlarm();
    }
  }
}