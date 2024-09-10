void main() {
  int x0, y0;
  int i = 0, j = 0;
  
  int receive_block;
  int image_to_draw;
  
  receive_block = -1;

  USBIP0_bit = 1;
  USBIP1_bit = 1;
  USBIP2_bit = 1;

  USBIE_bit = 1;

  EnableInterrupts();

  Start_TP();
  
  TFT_Fill_Screen(CL_WHITE);
  TFT_Set_Font(TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
  
  ClearBuffer(ReadBuffer, USB_LENGTH);
  ClearBuffer(WriteBuffer, USB_LENGTH);
  HID_Enable(ReadBuffer, &WriteBuffer);

  for(i=0; i<2; i++) {
      for(j=0; j<4; j++) {
               DrawIcon(j, i);
      }
  }
  
  while (1) {
    Check_TP();
    if (HID_Read()) {
       ClearBuffer(WriteBuffer, USB_LENGTH);
       if (strstr(ReadBuffer, "AT+SEND_IMAGE")) {
            strcpy(WriteBuffer, "READY");
            HID_Write(WriteBuffer,USB_LENGTH);
           receive_block = 0;
       }

       else if ((receive_block>=0)&&(receive_block<2048)) {
            memcpy((char *)Image_icon+receive_block, ReadBuffer, USB_LENGTH);
            strcpy(WriteBuffer, "OK");
            HID_Write(WriteBuffer,USB_LENGTH);
            receive_block+=USB_LENGTH;
       }
       
       else if (strstr(&ReadBuffer, "AT+DRAW_IMAGE=")) {
            image_to_draw = ReadBuffer[strlen("AT+DRAW_IMAGE=")]-'0';
            DrawIcon(image_to_draw%4, image_to_draw/4);
            strcpy(WriteBuffer, "OK");
            HID_Write(WriteBuffer,USB_LENGTH);
       }
    }
    ClearBuffer(&ReadBuffer, USB_LENGTH);
    if(receive_block > 2048-USB_LENGTH) receive_block = -1;
  }
}