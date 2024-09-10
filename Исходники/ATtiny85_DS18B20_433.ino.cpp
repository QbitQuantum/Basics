//-------------------------------------------------------------------------
float ReadSingleOneWireSensor(OneWire ds)
{
  //--- 18B20 stuff
  byte i;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius = 12.3;

  if (!ds.search(addr))
  {
    ds.reset_search();
    delay(250);
    return celsius;
  }

  if (OneWire::crc8(addr, 7) != addr[7])
  {
    return celsius;
  }

  //--- the first ROM byte indicates which chip
  switch (addr[0])
  {
  case 0x10:
    //Serial.println("  Chip = DS18S20");  // or old DS1820
    type_s = 1;
    break;
  case 0x28:
    // Serial.println("  Chip = DS18B20");
    type_s = 0;
    break;
  case 0x22:
    // Serial.println("  Chip = DS1822");
    type_s = 0;
    break;
  default:
    // Serial.println("Device is not a DS18x20 family device.");
    return celsius;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1 );  //--- start conversion, use alternatively ds.write(0x44,1) with parasite power on at the end

  delay(1000);        //--- maybe 750ms is enough, maybe not
                      //--- we might do a ds.depower() here, but the reset will take care of it.

  ds.reset();         //--- DS18B20 responds with presence pulse
                      //--- match ROM 0x55, sensor sends ROM-code command ommitted here.
  ds.select(addr);
  ds.write(0xBE);     //--- read scratchpad
  for (i = 0; i < 9; i++)
  {
    //--- we need 9 bytes, 9th byte is CRC, first 8 are data
    data[i] = ds.read();
  }

  //--- Convert the data to actual temperature
  //--- because the result is a 16 bit signed integer, it should
  //--- be stored to an "int16_t" type, which is always 16 bits
  //--- even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s)
  {
    raw = raw << 3;     //--- 9 bit resolution default
    if (data[7] == 0x10)
    {
      //--- "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    };
  }
  else
  {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    // default is 12 bit resolution, 750 ms conversion time
    if (cfg == 0x00) raw = raw & ~7;        // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3;   // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1;   // 11 bit res, 375 ms
  };

  celsius = (float)raw / 16.0;    //fahrenheit = celsius * 1.8 + 32.0;

  //---- Check if any reads failed and exit early (to try again).  
  if (isnan(celsius))
  {
    //--- signalize error condition 
    celsius = -99.9;
  };
  return celsius;
}