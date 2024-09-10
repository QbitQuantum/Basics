void BL_Bootloader(void) {
  S191_FileStatus fileStatus;
  
  DisableInterrupts;
#if PL_HAS_HW_SOUNDER
  Beep(1);
#endif
#if PL_BOOTLOADER_LCD
  if (JM_ELE_GetVal()!=0) {
    /* JM_ELE switch is off: the JM128 is controlling the LCD */
    LCD1_Init();
    LCD1_Clear();
  }
  PrintLCDText(0, "Bootloader mode: waiting for S19 file...");
#endif
  BLUSB1_InitUSB();
  
  fileStatus = S191_FILE_STATUS_NOT_STARTED;
  for(;;) {
    BLUSB1_PollAndProcessUSB(&fileStatus); /* Poll USB device for any input device */
    if(fileStatus==S191_FILE_STATUS_READING) {
    #if PL_BOOTLOADER_LCD
      PrintLCDText(1, "Loading S19 file...");
    #endif
      BL_flashErased = FALSE;
      BLUSB1_ReadAndProcessS19(&fileStatus);
      switch(fileStatus) {
        case S191_FILE_STATUS_FINISHED:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "Loading successful!\nYou can reset the board now.");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(1);
          #endif
          break;
        case S191_FILE_ERASE_FAILED:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "*** Flash erase error! ***");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(4);
          #endif
          break;
        case S191_FILE_FLASH_FAILED:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "*** Flash programming error! ***");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(6);
          #endif
          break;
        default:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "*** Error processing file! ***");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(8);
          #endif
          break;
      } /* switch */
    } /* if */    
  } /* for */
}