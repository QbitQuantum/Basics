int main(int argc, char *argv[]){

  unsigned char  addr, fc, data[256], crc[2];
  int datalen;
  char inport[100], outport[100];
  int i, j, len, err;
  int port;
  struct modbus_pdu *pdu;
  int cnt = 0x0;
  int id = 0x0;

  strcpy(inport,"/dev/ttyUSB0");
  strcpy(outport,"/dev/ttyUSB2");

   for (i=1;i<argc;i++) {
    if (strcmp(argv[i], "-inport") == 0) {
      len = strlen(argv[i+1]);
      if (len > 100) {
         printf("Error: Port name must be less then 100 characters long.\n");
         return(-1);
      };
      strncpy(inport, argv[i+1],len);
      i++;
      printf("INFO: Input port = %s\n", inport);
    } else if (strcmp(argv[i], "-outport") == 0) {
      len = strlen(argv[i+1]);
      if (len > 100) {
         printf("Error: Port name must be less then 100 characters long.\n");
         return(-1);
      }
      strncpy(outport, argv[i+1],len);
      i++;
    } else {
      printf("ERROR: Illegal argument (%s)\n", argv[i]);
      printf("Usage: %s -inport /dev/ttyXX -outport /dev/ttyYY\n", argv[0]);
      return (-1);
    }
  }

 port = openport(outport);
  if (port < 0) {
   return (port);
  }
  printf("open %s ok port = %d\n", outport, port);
  
  char *str;
  unsigned char lrc, top, bottom;
  while(1){
  for(cnt=0x01; cnt<=0x04; cnt++){
   for(id=0x00; id<=0xff; id++){
    addr = (unsigned char) 0x07;
    fc = (unsigned char) 0x2b;
    datalen = 3;
    data[0] = 0x0e;  //MEI type
    data[1] = cnt;   // ID code
    data[2] = id;  //object ID
  
    str = malloc(datalen + 2);
    str[0] = addr;
    str[1] = fc;
    memcpy(str+2, data, datalen);   
    lrc = LRC(str,datalen+2);
    free(str);    
    byte2ascii(lrc, &top, &bottom);
    crc[0] = top;
    crc[1] = bottom;
  
    pdu = mkpdu(addr, fc, data, datalen, crc);
    sendmodbus_ascii(port, pdu);
    freepdu(pdu);
    printf("number is %d\n", cnt);
    sleep(4);
   }
  }
 }
  
}