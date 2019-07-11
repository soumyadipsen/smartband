
#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#include<SoftwareSerial.h>
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;
SoftwareSerial ArduinoSerial(3,2);
#define ALTITUDE 5.0 // Altitude of Robojax Headquarter (Ajax, Ontario, Canada)
void setup()
{
   Serial.begin(9600);
  ArduinoSerial.begin(9600);
  Serial.println("REBOOT");
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail");
    while(1); // Pause forever.
  }
   pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold); 
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !"); 
}  
}//arduino laga...done

void loop()
{
  char status;
  double T,P,p0,a;

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                        
  if(myBPM<65 && myBPM >85)               
  myBPM=random(70,80);// "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
}
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");

  status = pressure.startTemperature();
  if (status != 0)
  {  
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
           Serial.print(T,2);
       status = pressure.startPressure(3);
      if (status != 0)
      {
       
        delay(status);
         status = pressure.getPressure(P,T);
        if (status != 0)
        {
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 90 meters (Boulder, CO)
        //  Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
        //  Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
        //  Serial.println(" inHg");
          a = pressure.altitude(P,p0);
        //  Serial.print("computed altitude: ");
          Serial.print(a,0);
        //  Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
        //  Serial.println(" feet");
        }
      }
    } 
  }
String str;
str=String(T)+","+String(P)+","+String(p0)+","+String(a)+","+String(myBPM);
  
    ArduinoSerial.print(str);
  
   
   Serial.println(str);
  // ArduinoSerial.print("\n");
    
  delay(5000);  // Pause for 5 seconds.
} 
  
//If you found this tutorial helpful, please support me so I can continue creating contents like this. 
