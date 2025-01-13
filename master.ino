#include <LiquidCrystal.h>
#include <Wire.h>

// LCD pin configuration
const int rs = 8, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Joystick pin configuration
const int JOY_X = A0;
const int JOY_Y = A1;
const int JOY_SW = 2;

// Menu items
const int NUM_ITEMS = 3;
String menuItems[NUM_ITEMS] = {"Clock", "Timer", "Alarm"};

int currentItem = 0;
int lastJoyY = 512;
bool joyPressed = false;

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  pinMode(JOY_SW, INPUT_PULLUP);
  updateMenu();
}

void loop() {
  Wire.beginTransmission(8);
  Wire.write("Test");
  Wire.endTransmission();
  navigateMenu();
  checkSelection();
  Wire.endTransmission();
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
    lcd.clear();
    lcd.print("Selected:");
    lcd.setCursor(0, 1);
    lcd.print(menuItems[currentItem]);
    delay(1500);
    updateMenu();
  } else if (digitalRead(JOY_SW) == HIGH) {
    joyPressed = false;
  }
}
