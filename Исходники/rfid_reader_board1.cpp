void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  client.connect(server, 3000);

  char store_id[30];
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i]);
  } 
	Serial.println();

  unsigned int hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];

  int  NFC_id=  (int)hex_num;

  sprintf(store_id,"%d" ,NFC_id);

  Serial.print("Store id is: ");
  Serial.println(store_id);

  char req[80];
  strcpy(req, "GET /?uid=");
  strcat(req, store_id);
  strcat(req, "&lat=48.139867&long=11.560935&sensor=MUCHbf HTTP/1.0");
    
  // Make a HTTP request:
  client.println(req);
  client.println();
  Serial.println("Request sent");
  Serial.println(req);

  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

}