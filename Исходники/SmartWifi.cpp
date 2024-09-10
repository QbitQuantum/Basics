void SmartWifi::SetupWifi(){
  EEPROM.begin(512);
  
  delay(10);
  printer->println();
  printer->println();
  printer->println("Startup");
  // read eeprom for ssid and pass
  String* credentials = getWifiCredentials();
  deviceId = getDeviceId()[0];
  String esid = credentials[0];
  String epass = credentials[1];
  printer->println("returned from function");
  printer->println("ssid "+ esid);
  printer->println("pass "+ epass);
  printer->println("deviceId "+ deviceId);
 
  if ( esid != "") {
      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      WiFi.begin(esid.c_str(), epass.c_str());
      if (testWifiConnection()) {

        //launchWeb(0);
        return;
      } 
  }
  setupMode = true;
  setupAP();
}