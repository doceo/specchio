void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect
 

void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(1000);
}

String dataMPU(){

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
  Serial.print("X: "); Serial.print(AcX);
  Serial.print("\t");
  Serial.print("Y: "); Serial.print(AcY);
  Serial.print("\n");
  Serial.print("Z: "); Serial.print(AcZ);
  Serial.print("\n");
  String data = "{" + String(ServoPitch) + "," + String(ServoRoll) + "}";
 
  return data;

}

 
//Funzione per il calcolo degli angoli Pitch e Roll
double FunctionsPitchRoll(double A, double B, double C){
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);
  
  Value = atan2(DatoA, DatoB);
  Value = Value * 180/3.14;
  
  return (int)Value;
}
 
//Funzione per l'acquisizione degli assi X,Y,Z del MPU6050
void FunctionsMPU(){  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
}


//funzioni utili alla connessione WiFi

//
//void printWiFiStatus() {
//  // print the SSID of the network you're attached to:
//  Serial.print("SSID: ");
//  Serial.println(WiFi.SSID());
//
//  // print your WiFi shield's IP address:
//  IPAddress ip = WiFi.localIP();
//  Serial.print("IP Address: ");
//  Serial.println(ip);
//
//  // print the received signal strength:
//  long rssi = WiFi.RSSI();
//  Serial.print("signal strength (RSSI):");
//  Serial.print(rssi);
//  Serial.println(" dBm");
//  // print where to go in a browser:
//  Serial.print("To see this page in action, open a browser to http://");
//  Serial.println(ip);
//}

