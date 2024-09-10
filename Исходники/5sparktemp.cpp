void oPrintTemp3(int index, float mytemp,  DeviceAddress passedAddress){
    oled.setFontType(0);
    oled.setCursor(0,0);
    oled.setCursor(0,index*12);
    oled.print(passedAddress[7],HEX);  // prints the last byte
    oled.print(" ");
    if (mytemp > 0 ) {
    oled.print(mytemp);
    }

    if (mytemp < 0 ) {
    oled.print("     ");

    Spark.publish("onewireloose", String(index) );
    Serial << "loose of onewire " << mytemp << "index " << index << endl;
    }
    oled.display();

}