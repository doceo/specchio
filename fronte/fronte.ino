#include <SPI.h>
#include <Wire.h>
#include <WiFi101.h>
#define MPU 0x68  // I2C address of the MPU-6050

char ssid[] = "makappa";      //  your network SSID (name)
char pass[] = "liberdiom";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)


double AcX,AcY,AcZ;
int Pitch, Roll;

int status = WL_IDLE_STATUS;
WiFiServer server(80);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_MPU(); // Inizializzazione MPU6050

   if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
   printWiFiStatus();

  }
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  FunctionsMPU(); // Acquisisco assi AcX, AcY, AcZ.
    
  Roll = FunctionsPitchRoll(AcX, AcY, AcZ);   //Calcolo angolo Roll
  Pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  //Calcolo angolo Pitch

  int ServoRoll = map(Roll, -90, 90, 0, 179);
  int ServoPitch = map(Pitch, -90, 90, 179, 0);

  Serial.println();

  Serial.print("Pitch: "); Serial.print(Pitch);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(Roll);
  Serial.print("\n");

  String data = "{" + String(ServoRoll) + "," + String(ServoPitch) + "}";
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client){
      Serial.println("new client");           // print a message out the serial port
      if (client.connected()){
        if(client.available()){
          char c = client.read();             // read a byte, then
          if (c=='\n'){
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(data);
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            
          }
        
      }
    
    }

  }
}
