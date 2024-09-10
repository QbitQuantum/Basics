void processSerialCommand()
{
  LCD_BACKLIGHT = 1;
  uartSendMsg("Check start\n");
  if (getChar() != 0xAA || getChar() != 0x55)
    return;
  uartSendMsg("Got start\n");
  unsigned char cmd = getChar();
  uartSendMsg("Got Command ");
  uartSendNum(cmd, 10);
  uartSendMsg("\n");

  switch(cmd)
  {
    case 'F':
      getFreqFromSerial(&radioSettings.rxFreqM, &radioSettings.rxFreqK);
      updateRDA1846Freq(radioSettings.rxFreqM, radioSettings.rxFreqK);
      break;
    case 'T':
      if(getChar() == '\r' && getChar() == '\n')
        rda1846TX();
      break;
    case 'R':
      if(getChar() == '\r' && getChar() == '\n')
        rda1846RX(1);
      break;
    case 'D':
      if(getChar() == '\r' && getChar() == '\n')
        rda1846TXDTMF(radioSettings.txDTMF, 6, 1000);
      break;
    case 'd':
      {
        uartSendMsg("Send Digital RTTY\n");

        unsigned char data = getChar()&0xFF;

        short time = getChar()&0xFF;
        time <<= 8;
        time |= getChar()&0xFF;

        if(getChar() == '\r' && getChar() == '\n')
          rda1846TXDigital(data, time,
              5796, //Mark 1.415Khz
              6492 //space 1.585Khz
              );
        uartSendMsg("Send Digital Done\n");
      }
      break;
    case 'S':
      {
        unsigned char addr = getChar()&0xFF;

        short data = getChar()&0xFF;
        data <<= 8;
        data |= getChar()&0xFF;

        if(getChar() == '\r' && getChar() == '\n')
        {
          uartSendMsg("Set: ");
          uartSendNum(addr, 16);
          uartSendMsg(" to ");
          uartSendNum(data, 16);
          uartSendMsg("\r\n");

          rda1846SetReg(addr, data); //, data);
        }
      }
      break;
  }
  LCD_BACKLIGHT = 0;

}