// Scan APs, use configured if found, otherwise try each open AP to get through, finally open soft AP with config page.
boolean WiFiManager::findOpenAP(const char *szUrl)
{
    int nOpen = 0;
    begin("ESP8266");
    int nScan = WiFi.scanNetworks();
    bool bFound = false;
    Serial.println("scan done");
    String sSSID = getSSID();
    int ind = 0;

    display.setFontScale2x2(false);
    if (nScan == 0) {
        Serial.println( "No APs found" );
        display.print("No APs Found");
    }
    else {
        for (int i = 0; i < nScan; ++i) // try each public AP
        {
            Serial.print(WiFi.SSID(i));
            Serial.print(" ");
            Serial.println(WiFi.encryptionType(i));
            display.print(WiFi.SSID(i));
            if(WiFi.encryptionType(i) == 7 /*&& strncmp(WiFi.SSID(i),"Chromecast",6) != 0*/)
            {
              display.drawString(128-8, 56, "O");
              nOpen++;
            }
            else if( sSSID == WiFi.SSID(i) ){ // The saved WiFi was found
              bFound  = true;
              display.drawString(128-8, 56, "<");
              Serial.println(" Cfg AP found");
            }
        }
  }

  if(nOpen == 0 && !bFound)
  {
    display.print("No open AP found");
    if(sSSID == "")
    {
       display.print("Switch to SoftAP");
       display.print("Hotspot: ESP8266");
       display.print("Goto 192.168.4.1");
    }else{
       display.print("Switching to");
       display.print(sSSID);
    }
  }

  delay(2000); // delay for reading

  if(nOpen && !bFound)
  {
    WiFi.mode(WIFI_STA);
    int counter = 0;
    for (int i = 0; i < nScan; ++i)
    {
      if(WiFi.encryptionType(i) == 7)   // run through open APs and try to connect
      {
        Serial.print("Attempting ");
        Serial.print(WiFi.SSID(i));
        display.print(String(WiFi.SSID(i)) + "...");
        WiFi.begin(WiFi.SSID(i));
        for(int n = 0; n < 50 && WiFi.status() != WL_CONNECTED; n++)
        {
          delay(200);
          Serial.print(".");
          display.clear();
          display.drawXbm(34,10, 60, 36, WiFi_Logo_bits);
          display.setColor(INVERSE);
          display.fillRect(10, 10, 108, 44);
          display.setColor(WHITE);
          drawSpinner(4, n % 4);
          display.display();
        }
        if(WiFi.status() == WL_CONNECTED)
        {
          Serial.println("Connected");
          display.print("Connected");
          if(attemptClient(szUrl))    // attemp port 80 and 8080
          {
            display.drawString(64-8, 56, "!");
            break;
          }else{
            display.drawString(64-8, 56, "X");
            WiFi.disconnect();
          }
        }
        counter++;
      }
    }
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Open WiFi failed");
      Serial.println("Switch to SoftAP");
      display.print("Open WiFi failed");
      display.print("Switch to SoftAP");
      autoConnect("ESP8266");
    }
  }
  else
  {
    autoConnect("ESP8266");
  }
  return true;
}