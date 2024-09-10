/*=============================
void LCDdisplay

inputs: int element, int value
returns: n/a

Based on the element, the LCD display
updates the needed value to be changed.
This function speaks to the LCD display
and tells it what to draw

Written by: Ben Wellington
Source: https://github.com/adafruit/Adafruit_ILI9340 (the ILI9340 libraries provided by adafruit)
=================================*/
void LCDdisplay(int element, int value) {

    Serial.print(F("Test "));//simple communication test

    if(element==ice) {
        //display power as 0 and mana as value and print (Cooldown) mode in blue
        lcd.fillRect(0, 155, 280, 55, ILI9340_BLACK);
        lcd.setCursor(300, 112);
        lcd.setTextColor(ILI9340_CYAN);
        lcd.setTextSize(2);
        lcd.print("           (Cooldown)");

        lcd.setCursor(300, 125);
        lcd.setTextColor(ILI9340_GREEN);
        lcd.setTextSize(4);
        for(int i = 0; i<=value; i++) {
            lcd.print("\5");//mana/tree character
        }//end for
        //lcd.fillRect(ManaBar, 148, 280, 52, ILI9340_BLACK);
    }
    else if(element == power) {
        //display power as value
        lcd.fillRect(5, 245, (value*59), 60, ILI9340_YELLOW);
        lcd.fillRect(((value*59)+5), 245, 280, 60, ILI9340_BLACK);
    }
    else if(element == damage) {
        if(value ==0) {
            //display health as zero and then print bow is dead
            lcd.fillScreen(ILI9340_BLACK);
            lcd.setCursor(0, 15);
            lcd.setTextColor(ILI9340_WHITE);
            lcd.setTextSize(4);
            lcd.print("   Your   weapon has  no more health and  is now     dead! ");
            lcd.setTextColor(ILI9340_RED);
            lcd.print("     :( ");
        }
        else {
            //display health as value
            lcd.fillRect(0, 50, 280, 60, ILI9340_BLACK);
            lcd.setCursor(300, 0);
            lcd.setTextColor(ILI9340_RED);
            lcd.setTextSize(7);
            for(int i = 0; i<=value; i++) {
                lcd.print("\3");//heart character
            }//end for
        }//end if
    }
    else if(element == plasma) {
        //bow has been fired
        lcd.fillRect(0, 245, 280, 60, ILI9340_BLACK);
        lcd.fillRect(0, 156, 280, 40, ILI9340_BLACK);//Paint over mana
        lcd.setCursor(300, 125);
        lcd.setTextColor(ILI9340_GREEN);
        lcd.setTextSize(4);
        for(int i = 0; i<=value; i++) {
            lcd.print("\5");//mana/tree character
        }//end for
        //dipslay power as zero and retrieve mana or use value
    }
    else if(element == 10) {
        //this is for when exiting cooldown
        //erase (cooldown) message
        lcd.fillRect(120, 120, 280, 30, ILI9340_BLACK);
    }
    else if(element == 5) {
        //show power bar as red because bow was fired
        lcd.fillRect(5, 245, (value*59), 60, ILI9340_RED);
        lcd.fillRect(((value*59)+5), 245, 280, 60, ILI9340_BLACK);
    }
    else {
        //invalid data received
        lcd.fillScreen(ILI9340_BLACK);
        lcd.setCursor(0, 15);
        lcd.setTextColor(ILI9340_WHITE);
        lcd.setTextSize(4);
        lcd.print("Invalid data was passed as an element.");
    }//end if

    Serial.println(F("Done!"));
}//LCDDisplay