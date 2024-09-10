void MyDisplay::update()
{
    Wire.lock();

#if DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
    display.clearDisplay();
    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("MySensors gateway");
    display.setTextSize(1);
    display.setCursor(0,9);
    if (AppSettings.wired)
    {
        if (!Network.getClientIP().isNull())
        {
            display.print("IP  :");
            display.println(Network.getClientIP().toString());
        } 
        else
        {
            display.setTextColor(BLACK, WHITE); // 'inverted' text
            display.println("connecting ...");
            display.setTextColor(WHITE);
        }
    }
    else
    {
        if (WifiStation.isConnected())
        {
            display.print("AP  :");
            display.println(Network.getClientIP().toString());
        } 
        else
        {
            display.setTextColor(BLACK, WHITE); // 'inverted' text
            display.println("connecting ...");
            display.setTextColor(WHITE);
        }
    }
    display.setCursor(0,18);
    if (isMqttConfigured())
    {
        display.print("MQTT:");
        display.println(MqttServer());
    }
    else
    {
        display.setTextColor(BLACK, WHITE); // 'inverted' text
        display.println("configure MQTT !");
        display.setTextColor(WHITE);
    }

    display.setCursor(0,27);
    display.println(SystemClock.getSystemTimeString().c_str());
    display.setCursor(0,36);
    display.print("HEAP :");
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println(system_get_free_heap_size());

    display.setTextColor(WHITE);

    //display.setTextColor(BLACK, WHITE); // 'inverted' text
    //display.setTextSize(3);
    display.display();
#elif DISPLAY_TYPE == DISPLAY_TYPE_20X4
    lcd.setCursor(0, 0);
    lcd.print((char *)"MySensors gateway   ");
    lcd.setCursor(0, 1);
    lcd.print((char *)build_git_sha);
    for (int i=0; i<(20-strlen((char *)build_git_sha)); i++)
        lcd.print(" ");
    lcd.setCursor(0, 2);
    lcd.print("HEAP :");
    String heap(system_get_free_heap_size());
    lcd.print(heap.c_str());
    for (int i=0; i<20-6-heap.length(); i++)
        lcd.print(" ");
    lcd.setCursor(0, 3);
    lcd.print("IP   :");
    String ip = Network.getClientIP().toString();
    lcd.print(ip.c_str());
    for (int i=0; i<20-6-ip.length(); i++)
        lcd.print(" ");
#endif

    Wire.unlock();
}