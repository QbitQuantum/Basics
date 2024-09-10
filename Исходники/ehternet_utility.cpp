void sendData()
{
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect("kaylee.markild.no", 80))
  
  {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.println("GET /crap/test.txt HTTP/1.1");
    client.println("GET /crap/test.txt HTTP/1.1");
    Serial.println("Host: kaylee.markild.no");
    client.println("Host: kaylee.markild.no");
    Serial.println("User-Agent: ArduinoUno/r3 Ethernet Shield");
    client.println("User-Agent: ArduinoUno/r3 Ethernet Shield");
    Serial.println("Accept: */*");
    client.println("Accept: */*");    
    client.println();
  }
  else
  {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}