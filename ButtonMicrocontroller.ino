#include <LiquidCrystal.h>
#include <Wire.h>
// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(A0, A1, A2, A3, 11, 10);
const int buttonPin1 = 13;
const int buttonPin2 = 12;
int buttonState1 = 0;
int buttonState2 = 0;
int value = 0;
char space[] = "       ";
char fullspace[] = "                ";
// ------------------------------------------------------ SETUP FUNCTION
void setup()
{
  // LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(115200);
  Wire.begin();
}
// ------------------------------------------------------ LOOP FUNCTION
void loop()
{
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState1 == HIGH && buttonState2 == HIGH)
  {
    // Turn on display
    lcd.setCursor(0, 1);
    lcd.print("    Charging    ");
    delay(2000);
    lcd.print(" Fully Charged  ");
    delay(2000);
  }
  else
  {
    // Resetting to basic apperance
    lcd.setCursor(0, 0);
    lcd.print("Solar Powered RC");
    lcd.setCursor(0, 1);
    lcd.print(fullspace);
  }
}
