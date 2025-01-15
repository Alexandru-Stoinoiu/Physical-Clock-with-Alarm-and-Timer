#include <LiquidCrystal.h>
#include <Wire.h>

#define MASTER_ADDRESS 3

// LCD pin configuration
const int rs = 8, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Joystick pin configuration
const int JOY_X = A0;
const int JOY_Y = A1;
const int JOY_SW = 2;

// Menu items
const int NUM_ITEMS = 4;
String menuItems[NUM_ITEMS] = {"Clock", "Timer", "Alarm", "StopAlarm"};

int currentItem = 0;
int lastJoyY = 512;
bool joyPressed = false;
bool alarmRinging = false;

void setup() {
  Wire.begin(MASTER_ADDRESS);
  lcd.begin(16, 2);
  pinMode(JOY_SW, INPUT_PULLUP);
  updateMenu();
  Serial.begin(9600);
}

void loop() {
  if (!alarmRinging) {
    navigateMenu();
  }
  checkSelection();
  handleAlarmRinging();
}

void updateMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("> " + menuItems[currentItem]);
  lcd.setCursor(0, 1);
  lcd.print("  " + menuItems[(currentItem + 1) % NUM_ITEMS]);
}

void navigateMenu() {
  int joyY = analogRead(JOY_Y);
  
  if (joyY < 300 && lastJoyY >= 300) {
    currentItem = (currentItem - 1 + NUM_ITEMS) % NUM_ITEMS;
    updateMenu();
  } else if (joyY > 700 && lastJoyY <= 700) {
    currentItem = (currentItem + 1) % NUM_ITEMS;
    updateMenu();
  }
  
  lastJoyY = joyY;
}

void checkSelection() {
  if (digitalRead(JOY_SW) == LOW && !joyPressed) {
    joyPressed = true;
    if (alarmRinging) {
      stopAlarm();
    } else {
      lcd.clear();
      lcd.print("Selected:");
      lcd.setCursor(0, 1);
      lcd.print(menuItems[currentItem]);
      if (menuItems[currentItem] == "Clock") {
        Wire.beginTransmission(8);
        Wire.write("Clock");
        Wire.endTransmission();
      } else if (menuItems[currentItem] == "Alarm") {
        setAlarm();
      } else if (menuItems[currentItem] == "Timer") {
        setTimer();
      } else if (menuItems[currentItem] == "StopAlarm"){
        Serial.println("STOOOP");
        Wire.beginTransmission(8);
        Wire.write("StopA");
        Wire.endTransmission();
      }
      delay(1500);
      updateMenu();
    }
  } else if (digitalRead(JOY_SW) == HIGH) {
    joyPressed = false;
  }
}

void stopAlarm() {
  Wire.beginTransmission(8);
  Wire.write("StopAlarm");
  Wire.endTransmission();
  alarmRinging = false;
  updateMenu();
}

void handleAlarmRinging() {
  if (alarmRinging) {
    lcd.clear();
    lcd.print("Alarm is ringing");
    lcd.setCursor(0, 1);
    lcd.print("Press to stop");
  }
}

void setAlarm() {
  int alarmHour = 0;
  int alarmMinute = 0;
  setTime("Alarm", alarmHour, alarmMinute);
  
  Wire.beginTransmission(8);
  Wire.write("Alarm");
  Wire.write(alarmHour);
  Wire.write(alarmMinute);
  Wire.endTransmission();
  
  displaySetTime("Alarm set to:", alarmHour, alarmMinute);
}

void setTimer() {
  int timerHour = 0;
  int timerMinute = 0;
  setTime("Timer", timerHour, timerMinute);
  
  Wire.beginTransmission(8);
  Wire.write("Timer");
  Wire.write(timerHour);
  Wire.write(timerMinute);
  Wire.endTransmission();
  
  displaySetTime("Timer set to:", timerHour, timerMinute);
}

void setTime(const char* mode, int &hours, int &minutes) {
  int lastJoyY = analogRead(JOY_Y);
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 50;
  bool joyMoved = false;
  bool buttonPressed = false;

  delay(500);

  // Set hour
  while (true) {
    lcd.clear();
    lcd.print("Set ");
    lcd.print(mode);
    lcd.print(" Hour:");
    lcd.setCursor(0, 1);
    lcd.print(hours);
    
    int joyY = analogRead(JOY_Y);
    if (abs(joyY - lastJoyY) > 50) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (joyY < 300 && !joyMoved) {
        hours = (hours - 1 + 24) % 24;
        joyMoved = true;
      } else if (joyY > 700 && !joyMoved) {
        hours = (hours + 1) % 24;
        joyMoved = true;
      } else if (joyY >= 300 && joyY <= 700) {
        joyMoved = false;
      }
    }

    lastJoyY = joyY;
    
    if (digitalRead(JOY_SW) == LOW && !buttonPressed) {
      buttonPressed = true;
      delay(50);
    } else if (digitalRead(JOY_SW) == HIGH && buttonPressed) {
      buttonPressed = false;
      break;
    }
    
    delay(50);
  }
  
  // Set minute (similar structure as hour setting)
  lastJoyY = analogRead(JOY_Y);
  joyMoved = false;
  buttonPressed = false;
  
  while (true) {
    lcd.clear();
    lcd.print("Set ");
    lcd.print(mode);
    lcd.print(" Minute:");
    lcd.setCursor(0, 1);
    lcd.print(minutes);
    
    int joyY = analogRead(JOY_Y);
    if (abs(joyY - lastJoyY) > 50) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (joyY < 300 && !joyMoved) {
        minutes = (minutes - 1 + 60) % 60;
        joyMoved = true;
      } else if (joyY > 700 && !joyMoved) {
        minutes = (minutes + 1) % 60;
        joyMoved = true;
      } else if (joyY >= 300 && joyY <= 700) {
        joyMoved = false;
      }
    }

    lastJoyY = joyY;
    
    if (digitalRead(JOY_SW) == LOW && !buttonPressed) {
      buttonPressed = true;
      delay(50);
    } else if (digitalRead(JOY_SW) == HIGH && buttonPressed) {
      buttonPressed = false;
      break;
    }
    
    delay(50);
  }
}

void displaySetTime(const char* message, int hours, int minutes) {
  lcd.clear();
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  delay(2000);
}