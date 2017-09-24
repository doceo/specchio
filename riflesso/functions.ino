

void avviaServo() {

    serX.attach(5);
    serY.attach(6);
    serX.writeMicroseconds(1500);
    serY.writeMicroseconds(1500);  
}


void spegniServo() {

    serX.detach();
    serY.detach();

}

void servoCentro(int pos){

    serX.write(pos);              
    serY.write(pos);            
  
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /index.php HTTP/1.1");
    client.println("Host: diomede-arduino");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

int estraX (String str){
  int openGraf, coma, valX;
  String strX;
  
  openGraf = str.lastIndexOf('{');
 
  coma = str.lastIndexOf(',');
  
  strX=str.substring(openGraf+1,coma);
 
  valX = strX.toInt();
  Serial.println(valX);
  return valX;
 
}

int estraY (String str){
  int closeGraf, coma, valY;
  String strY;
  
  closeGraf = str.lastIndexOf('}');

  
  coma = str.lastIndexOf(',');
 
  strY=str.substring(coma+1,closeGraf);
  
  valY = strY.toInt();

  Serial.println(valY);
  return valY;
 
}

