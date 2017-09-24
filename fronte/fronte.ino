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
    // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status

}

void loop() {
  
  // put your main code here, to run repeatedly:
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client){
//      Serial.println("new client");           // print a message out the serial port
      if (client.connected()){
        if(client.available()){
          char c = client.read();             // read a byte, then
          if (c=='\n'){

            String data = dataMPU();
            
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
            client.stop();
            Serial.println("client disonnected");
          }
        
      }
    
    }

  }
}
