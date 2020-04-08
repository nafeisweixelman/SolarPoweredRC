#include <Wire.h>
//A5 = SCL, A4 = SDA
byte ADDRESS = 0x61, MSB_STATE = 0x06, LSB_STATE = 0xE0;
byte MSB_V = 0x06, LSB_V = 0xE4;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(MSB_V); // MSB of State Register
  Wire.write(LSB_V); // LSB of State Register
  int error = Wire.endTransmission(false);
  if (error != 0)
    Serial.println("\tError, no device found at 0x61");

  int n = Wire.requestFrom(ADDRESS, byte(8));
  if (n != 8)
  {
    Serial.println("\trequestFrom failed");
  }
  else
  {
    for (int i = 0; i < 8; i ++)
    {
      Serial.print(Wire.read());
      Serial.print(" ");
    }
    Serial.println("");
  }
  delay(2000);
}
