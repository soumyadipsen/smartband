#include<SoftwareSerial.h>
SoftwareSerial ArduinoSerial(3,2);
void setup() {
  Serial.begin(9600);
  ArduinoSerial.begin(9600);
  // put your setup code here, to run once:
  
}

void loop() {
  while (ArduinoSerial.available()>0){
    float val=random(1,100);
   ArduinoSerial.print(val);
   ArduinoSerial.print("\n");
    }
  
  delay(100);
  // put your main code here, to run repeatedly:

}
