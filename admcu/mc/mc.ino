#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>
SoftwareSerial ss(D2,D3);
const char* ssid = "senwlan";
const char* password = "Bittusen";
unsigned long previousMillis = 0;
//unsigned long currentMillis = 0;
 const long interval = 15000;  
#define myPeriodic 15 //in sec | Thingspeak pub is 15sec
float prevTemp = 0;
String str="";
const char* server = "api.thingspeak.com";
String apiKey ="AIIY6Y4IAJLPECDP";
int sent = 0;

void connectWifi()
{
  Serial.println("Connecting to....");
  Serial.print("Connecting to "+*ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  }
}//end connect

void setup() {
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  Serial.begin(115200);
  ss.begin(9600);
  // put your setup code here, to run once:
  WiFi.disconnect();//disconnect from previously connected Access points
  delay(10);
  WiFi.begin(ssid,password);//begin connecting to the given ssid and pass
Serial.println("Connecting to");
while(WiFi.status()!=WL_CONNECTED)//when not connected
{
  Serial.print(".");//print dots
  delay(500);
}
}

String serialResponse = "";
WiFiClient client;
void loop() {
String T,P,p0,a,pul;
int p;



   if(ss.available()>0)
     {  
          str=ss.readString();
    //char ch=esp.read();
    //str+=(char)ch;
    //Serial.println(str);
  
    char buf[str.length()];
    str.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *str1,*str2,*str3,*str4,*str5;
    //while ((str1 = strtok_r(p, ",", &p)) != NULL) 
    str1 = strtok_r(p, ",", &p);
    str2 = strtok_r(p, ",", &p);
    str3 = strtok_r(p, ",", &p);
    str4 = strtok_r(p, ",", &p);
    str5 = strtok_r(p, ",", &p);
    T=String(str1);
    P=String(str2);
    p0=String(str3);
    a=String(str4);
    pul=String(str5);
      Serial.println(str1);
      Serial.println(str2);
      Serial.println(str3);
      Serial.println(str4);
      Serial.println(str5);
    
  }
  delay(5000);
  // put your main code here, to run repeatedly:
 String tsData="";
   if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
   Serial.println("WiFi Client connected ");
   
    tsData=apiKey;
    tsData+="&field1=";
    tsData+=T;
    tsData+="&field2=";
    tsData+=P;
    tsData+="&field3=";
    tsData+=p0;
    tsData+="&field4=";
    tsData+=a; 
    tsData+="&field5=";
    tsData+=pul;  
    tsData += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(tsData.length());
   client.print("\n\n");
   client.print(tsData);
   delay(10);
   
   }//end if
   sent++;
 client.stop();
}
