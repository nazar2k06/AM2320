#include <AM2320.h>

float t, h;

AM2320 am;
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("~~~~~~~~~~~");
  Serial.print("Status: ");
  switch(am.status()) {
  case 0:
    Serial.println("OK");
    break;
  case 1:
    Serial.println("Read request error");
    break;
  case 2:
    Serial.println("Receive error");
    break;
  case 3:
    Serial.println("Receive function code error");
    break;
  case 4:
    Serial.println("CRC error");
    break;
  }
  delay(1000);

  Serial.print("\nRead: ");
  switch(am.read(&t, &h)) {
  case 0:
    Serial.println("OK");
    break;
  case 1:
    Serial.println("Read request error");
    break;
  case 2:
    Serial.println("Receive error");
    break;
  case 3:
    Serial.println("Receive function code error");
    break;
  case 4:
    Serial.println("CRC error");
    break;
  }
  Serial.println(String("T: ") + t);
  Serial.println(String("H: ") + h);
  delay(1000);

  Serial.println(String("\nRead temp: ") + am.getT());
  delay(1000);
  Serial.println(String("Read humidity: ") + am.getH());
  Serial.println("~~~~~~~~~~~");
  
  delay(3000);
}
