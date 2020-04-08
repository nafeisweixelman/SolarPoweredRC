#include <LiquidCrystal.h>
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Charge = 5;           //Pin to connect or disconnect the battery to the circuit
int Mode = 6;             //Pin to toggle between CC mode and CV mode
int voltageDivider = 7;   //To measure battery Voltage
int shuntResistor = 8;    //To measure charging current
float Voltage;
float Current;
// ---------------------------------------------------------------- SETUP FUNCTION
void setup() {
  lcd.begin(16, 2);
  pinMode (Charge, OUTPUT);
  pinMode (Mode, OUTPUT);
  digitalWrite(Charge, HIGH);   //Begin Charging Initially by connecting the battery
  digitalWrite(Mode, LOW);      //HIGH for CV mode and LOW of CC mode, initally CC mode
  delay(500);
}
// ---------------------------------------------------------------- LOOP FUNCTION
void loop() {
  Voltage = analogRead(voltageDivider) * 0.0095;    //Measure Battery Voltage
  Current = analogRead(shuntResistor) * 2.64;       //Measure Charging Current

  // -------------------------------------------------------------- CONSTANT CURRENT MODE
  while (Voltage < 8.2)
  {
    digitalWrite(Mode, LOW); //Stay in CC mode

    Voltage = analogRead(voltageDivider) * 0.0095;  //Measure Battery Voltage
    Current = analogRead(shuntResistor) * 2.64;     //Measure Charging Current

    lcd.print(" V = "); lcd.print(Voltage);
    lcd.setCursor(0, 1);
    lcd.print(" CC ");
    delay(500);
    lcd.clear();

    if (Current >= 8.2)
    {
      digitalWrite(Mode, HIGH);
      break;
    }
  }

  // -------------------------------------------------------------- CONSTANT VOLTAGE MODE
  while (Voltage >= 8.2)
  {
    digitalWrite(Mode, HIGH);

    Voltage = analogRead(voltageDivider) * 0.0095;  //Measure Battery Voltage
    Current = analogRead(shuntResistor) * 2.64;     //Measure Charging Current

    lcd.print(" V = "); lcd.print(Voltage);
    lcd.setCursor(0, 1);
    lcd.print(" CV");
    lcd.print(" I = "); lcd.print(Current);
    lcd.setCursor(0, 1);
    delay(500);
    lcd.clear();

    //Check if the battery is charged by monitoring charging current
    if (Current < 50) //If yes
    {
      digitalWrite(Charge, LOW);
      // Keep the charger off until restart
      while (1)
      {
        lcd.setCursor(0, 1);
        lcd.print("Charge Complete");
        delay(500);
        lcd.clear();
      }
    }
  }
}
