
/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 */

#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>

Servo serX;
Servo serY;

int X, angX;
int Y, angY;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(1, 1, 1, 1);


EthernetClient client;

//char server[] = "diomede-rasp.local";
IPAddress server(192,168,1,68);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  
  }
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  Serial.println("posiziono i servo");
  avviaServo();
  servoCentro(90);
  spegniServo();
  
}


void loop() {

char c;
String varGet;
int valX, valY;


    delay(1000);
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {
    c = client.read(); 
    varGet  += c;
 //   Serial.print(c);
  }
  Serial.println();
  Serial.println(varGet);
  
  valX=estraX(varGet);
  valY=estraY(varGet);
  
  Serial.print(valX + " ");
  Serial.println(valY);
  avviaServo();

    serX.write(valX);              // tell servo to go to position in variable 'pos'
    serY.write(valY);              // tell servo to go to position in variable 'pos'

//    serY.write(pos);              // tell servo to go to position in variable 'pos'
    delay(150);    
  
  spegniServo();
  
  httpRequest();

}

