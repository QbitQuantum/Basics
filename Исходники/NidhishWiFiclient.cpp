String sendData(String tcpHeader, String data){
  int x;
  SerialUSB.println("Wi-Fi Sending data...");
  Serial1.setTimeout(5000);
  Serial1.println(tcpHeader);
  Serial1.flush();
  Serial1.println(data);
  Serial1.flush();
  String response = Serial1.readStringUntil(Serial1.available());
  if(response.length() > 2){
    x = findString("OK", response);
  } 
  else{
    SerialUSB.println("Wi-Fi Sending data Timeout!");
    return "";
  }

  if(x != -1){
    SerialUSB.println("Wi-Fi data sent");
    response.remove(0, findString("alive",response) + 9);
    Serial1.setTimeout(1000);
    return response;
  }
  else{
    SerialUSB.println("Wi-Fi couldn't send the data!");
    Serial1.setTimeout(1000);
    return "";
  }

}