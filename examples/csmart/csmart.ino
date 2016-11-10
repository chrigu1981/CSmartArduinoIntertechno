#include <CSmartIntertechno.h>
CSmartIntertechno csmart(4);
int id    = 1234567;
int unit  = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  csmart.dim(id,unit,100);
  delay(2000);
  csmart.dim(id,unit,70);
  delay(2000);
  csmart.dim(id,unit,40);
  delay(2000);
  csmart.turnOff(id,unit);
  delay(2000);
  csmart.turnOn(id,unit);
  delay(2000);
  csmart.turnOff(id,unit);
  delay(2000);
}
