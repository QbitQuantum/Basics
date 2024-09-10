void DrawBootloaderScreen(void)
{
#if BOOTLOADER
  FillMyBuffer(STARTING_ROW, LCD_ROW_NUM, 0x00);
  CopyRowsIntoMyBuffer(pBootloader, BOOTLOADER_START_ROW, BOOTLOADER_ROWS);
  
  // Draw version
  SetFont(MetaWatch5);
  gRow = 61;
  gColumn = 4;
  gBitColumnMask = BIT3;
  DrawString("V ", DRAW_OPT_BITWISE_OR);
  DrawString((char const *)VERSION, DRAW_OPT_BITWISE_OR);

  unsigned char i = 0;
  char const *pBootVer = BootVersion;

  PrintF("BL_VER addr:%04X", pBootVer);
  for (; i < 8; ++i) {PrintH(pBootVer[i]); PrintC(SPACE);}
  i = 0;

  while (*pBootVer && i++ < 8)
  {
    if ((*pBootVer < ZERO || *pBootVer > '9') && *pBootVer != '.') break;
    pBootVer ++;
  }
  
  if (i > 4) // at least x.x.x
  {
    gRow += 7;
    gColumn = 4;
    gBitColumnMask = BIT3;
    DrawString("B ", DRAW_OPT_BITWISE_OR);
    DrawString(BootVersion, DRAW_OPT_BITWISE_OR);
  }

  DrawLocalAddress(1, 80);
  
  SendMyBufferToLcd(STARTING_ROW, LCD_ROW_NUM);
#endif
}