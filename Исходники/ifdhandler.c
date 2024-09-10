RESPONSECODE IFDHCloseChannel ( DWORD Lun ) {
  
  /* This function should close the reader communication channel
     for the particular reader.  Prior to closing the communication channel
     the reader should make sure the card is powered down and the terminal
     is also powered down.

     returns:

     IFD_SUCCESS
     IFD_COMMUNICATION_ERROR     
  */
  /* TODO: power down the card */
  
  //int readerNum = (Lun & 0xFFFF0000) >> 16;
  
  closeDriver(Lun);
  
  return IFD_SUCCESS;
}