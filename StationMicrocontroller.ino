#include <LiquidCrystal.h>
#include <Wire.h>
// LiquidCrystal(rs, enable, d4, d5, d6, d7)
// A5 is SCL pin, A4 is SDA
// GND, SDA, SCL
LiquidCrystal lcd(A0, A1, A2, A3, 11, 10);
byte ADDRESS = 0x61, MSB_STATE = 0x06, LSB_STATE = 0xE0;
int STATE;
char fullspace[] = "                ";
bool DEBUG = false;
void setup()
{
  lcd.begin(16, 2);
  if (DEBUG == true)
    Serial.begin(115200);
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(MSB_STATE);
  Wire.write(LSB_STATE);
  Wire.requestFrom(ADDRESS, byte(1));
  STATE = (Wire.read());
  if (DEBUG == true)
    Serial.println(STATE);
  switch (STATE)
  {
    case 2:
      {
        lcd.setCursor(0, 0);
        lcd.print("Solar Powered RC");
        lcd.setCursor(0, 1);
        lcd.print("      Idle      ");
        if (DEBUG == true)
          Serial.println("IDLE");
        Wire.endTransmission();
        break;
      }
    case 9:
      {
        lcd.setCursor(0, 0);
        lcd.print("Solar Powered RC");
        lcd.setCursor(0, 1);
        lcd.print("    Charging    ");
        if (DEBUG == true)
          Serial.println("CHARGING");
        Wire.endTransmission();
        break;
      }
    case 11:
      {
        lcd.setCursor(0, 0);
        lcd.print("Solar Powered RC");
        lcd.setCursor(0, 1);
        lcd.print(" Fully Charged! ");
        Wire.endTransmission();
        break;
      }
    default:
      {
        lcd.setCursor(0, 0);
        lcd.print("Solar Powered RC");
        lcd.setCursor(0, 1);
        lcd.print(fullspace);
        Wire.endTransmission();
      }
  }
  Wire.endTransmission();
  delay(2000);
}
