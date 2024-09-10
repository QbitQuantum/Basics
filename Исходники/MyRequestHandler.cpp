void MyFunctionRequestHandler::apiHandler(ESP8266WebServer& server) {
  mpIpDisplay->StopShowingIp();
  //applicationProblems = -1;  //force repaint display in client mode

  // adjust logo brightness (on/off right now)
  if (server.hasArg(F("logo"))) {
    if (server.arg(F("logo")).equals(F("on"))) {
      mpLedstripLogo->setBrightness(255);
    } else if (server.arg(F("logo")).equals(F("default"))) {
       ledsSetLogoDefault();
    } else {
       mpLedstripLogo->setBrightness(0);
    }
  }

  // to quickly set the RGB colors of the logo remotely
  if (server.hasArg(F("logoled"))) {
    byte led = byte(server.arg(F("logoled")).toInt());
    byte r = byte(server.arg(F("r")).toInt());
    byte g = byte(server.arg(F("g")).toInt());
    byte b = byte(server.arg(F("b")).toInt());
    mpLedstripLogo->setPixelColor(led, r, g, b);
  }

  if (server.hasArg(F("top_init"))){
    mpDisplayUpperRing->Init();
  }
  if (server.hasArg(F("top"))){
    String argument = server.arg(F("top"));
    unsigned int i = 0;
    unsigned int ret = 0;
    
    while (i < argument.length())
      i = mpDisplayUpperRing->ParseLedArg(argument, i);
  }
  if (server.hasArg(F("top_bg"))){
    String argument = server.arg(F("top_bg"));
    if (argument.length() == 6)
      mpDisplayUpperRing->SetBackground(argument.substring(2, 4) + argument.substring(0, 2) + argument.substring(4, 6)); 
  }
  if (server.hasArg(F("top_whirl"))){
    String argument = server.arg(F("top_whirl"));
    mpDisplayUpperRing->ParseWhirlArg(argument);
  } 
  if (server.hasArg(F("top_morph"))){
    String argument = server.arg(F("top_morph"));
    mpDisplayUpperRing->ParseMorphArg(argument);
  } 
    
  if (server.hasArg(F("bottom_init"))){
    mpDisplayLowerRing->Init();
  }
  if (server.hasArg(F("bottom"))){
    String argument = server.arg(F("bottom"));
    unsigned int i = 0;
    unsigned int ret = 0;
    
    while (i < argument.length())
      i = mpDisplayLowerRing->ParseLedArg(argument, i);
  }
  if (server.hasArg(F("bottom_bg"))){
    String argument = server.arg(F("bottom_bg"));
    if (argument.length() == 6)
      mpDisplayLowerRing->SetBackground(argument.substring(2, 4) + argument.substring(0, 2) + argument.substring(4, 6)); 
  }
  if (server.hasArg(F("bottom_whirl"))){
    String argument = server.arg(F("bottom_whirl"));
    mpDisplayLowerRing->ParseWhirlArg(argument);
  } 
  if (server.hasArg(F("bottom_morph"))){
    String argument = server.arg(F("bottom_morph"));
    mpDisplayLowerRing->ParseMorphArg(argument);
  } 

  if (server.hasArg(F("dynatrace-environmentid")) && server.hasArg(F("dynatrace-apikey")) && server.hasArg(F("dynatrace-interval"))) {
    if (mDebug) Serial.println(F("Storing Dynatrace SaaS/Managed environment integration settings"));
    mpConfig->enabled = server.hasArg(F("dynatrace-on"));
    mpConfig->dynatraceEnvironmentID = server.arg(F("dynatrace-environmentid"));
    mpConfig->dynatraceApiKey = server.arg(F("dynatrace-apikey"));
    mpConfig->pollingIntervalS = server.arg(F("dynatrace-interval")).toInt();
    mpConfig->SignalChange();
    mpConfig->Write();
    server.sendHeader(F("location"), F("/"));
    server.send(302);
    return;
  }

  if (server.hasArg(F("hostname"))) {
    String newWifiHostname = server.arg(F("hostname"));
    eepromSet(newWifiHostname);
  }

  // note its required to provide both arguments SSID and PWD
  if (server.hasArg(F("ssid")) && server.hasArg(F("pwd"))) {
    String newWifiSSID = server.arg(F("ssid"));
    String newWifiPwd = server.arg(F("pwd"));

    // if SSID is given, also update wifi credentials
    if (newWifiSSID.length()) {
      WiFi.mode(WIFI_STA);
      WiFi.begin(newWifiSSID.c_str(), newWifiPwd.c_str() );
    }

    if (mDebug) {
      Serial.println(String(F("New Wifi settings: ")) + newWifiSSID + F(" / ") + newWifiPwd);
      Serial.println(String(F("Restarting....")));
      Serial.flush();
    }

    httpReboot(server, String(F("New WIFI settings accepted. Mac address: ")) + WiFi.macAddress() + String(F("<p/>")));

  }

 
  server.sendHeader(F("cache-control"), F("private, max-age=0, no-cache, no-store"));
  server.send(200);
}