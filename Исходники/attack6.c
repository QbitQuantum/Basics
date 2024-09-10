int main(int argc, char *argv[]){

  unsigned char addr, fc, data[256], crc[2];
  int datalen;
  char inport[100], outport[100];
  int i, j, len, err;
  int port;
  struct modbus_pdu *pdu;
  int cnt1 = 0, cnt2 = 0x0, cnt;
  
  strcpy(inport, "/dev/ttyUSB2");
  strcpy(outport, "/dev/ttyUSB0");
  
  for(i=1; i<argc; i++){
    if(strcmp(argv[i], "-inport") == 0){
      len = strlen(argv[i+1]);
      if(len > 100){
        printf("Error: Port name must be less than 100 characters long.\n");
        return(-1);
      }
      strncpy(inport, argv[i+1], len);
      i++;
      printf("INFO: Input port = %s\n", inport);
    } else if(strcmp(argv[i], "-outport") == 0){
      len = strlen(argv[i+1]);
      if(len > 100){
        printf("Error: Port name must be less than 100 characters long.\n");
        return(-1);
      }
      strncpy(outport, argv[i+1],len);
      i++;      
    }else{
      printf("ERROR: Illegal arguments (%s)\n", argv[i]);
      printf("Usage: %s -inport /dev/ttyXX -outport /dev/ttyYY\n", argv[0]);
      return (-1);
    }
  }
   
  port = openport(outport);
  if(port < 0)
    return (port);
  printf("open %s ok port = %d\n", outport, port);
  
  char *str;
  unsigned char lrc, top, bottom;
  addr = (unsigned char) 0x4; 

  //fc =0x01 read coil,
  while(1){

   cnt1 = 0;
  for(cnt1=0; cnt1<100; cnt1++){
  fc = (unsigned char) 0x01;
  datalen = 19;
  data[0] = 0x00;
  data[1] = 0x00;
  data[2] = 0x00;
  data[3] = 0x00;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  data[8] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;
  data[12] = 0x00;
  data[13] = 0x00;
  data[14] = 0x00;
  data[15] = 0x00;
  data[16] = 0x00;
  data[17] = 0x00;
  data[18] = 0x00;


  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);     
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;
  
  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt1);
  sleep(1);
  }

   for(cnt1=0; cnt1<100; cnt1++){
  fc = (unsigned char) 0x01;
  datalen = 19;
  data[0] = 0xff;
  data[1] = 0xff;
  data[2] = 0xff;
  data[3] = 0xff;
  data[4] = 0xff;
  data[5] = 0xff;
  data[6] = 0xff;
  data[7] = 0xff;
  data[8] = 0xff;
  data[9] = 0xff;
  data[10] = 0xff;
  data[11] = 0xff;
  data[12] = 0xff;
  data[13] = 0xff;
  data[14] = 0xff;
  data[15] = 0xff;
  data[16] = 0xff;
  data[17] = 0xff;
  data[18] = 0xff;
   str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt1);
  sleep(1);
  }
 
  //fc = 0x02 Read Discrete Inputs, not implement excode = 01
  fc = (unsigned char)0x02;
  for(cnt1=0; cnt1<100; cnt1++){
   datalen = 19;
  data[0] = 0x00;
  data[1] = 0x00;
  data[2] = 0x00;
  data[3] = 0x00;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  data[8] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;
  data[12] = 0x00;
  data[13] = 0x00;
  data[14] = 0x00;
  data[15] = 0x00;
  data[16] = 0x00;
  data[17] = 0x00;
  data[18] = 0x00;
 
  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;
  
  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt);
  sleep(1);
  }

  for(cnt1=0; cnt1<100; cnt1++){
  fc = (unsigned char) 0x02;
  datalen = 19;
  data[0] = 0xff;
  data[1] = 0xff;
  data[2] = 0xff;
  data[3] = 0xff;
  data[4] = 0xff;
  data[5] = 0xff;
  data[6] = 0xff;
  data[7] = 0xff;
  data[8] = 0xff;
  data[9] = 0xff;
  data[10] = 0xff;
  data[11] = 0xff;
  data[12] = 0xff;
  data[13] = 0xff;
  data[14] = 0xff;
  data[15] = 0xff;
  data[16] = 0xff;
  data[17] = 0xff;
  data[18] = 0xff;
  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt1);
  sleep(1);
  }

  //fc = 0x03 Read Holding Registers, not implement excode = 01
  fc = 0x03;
  for(cnt1=0; cnt1<100; cnt1++){
  datalen = 19;
  data[0] = 0x00;
  data[1] = 0x00;
  data[2] = 0x00;
  data[3] = 0x00;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  data[8] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;
  data[12] = 0x00;
  data[13] = 0x00;
  data[14] = 0x00;
  data[15] = 0x00;
  data[16] = 0x00;
  data[17] = 0x00;
  data[18] = 0x00;

  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;
  
  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("numb is %d\n", cnt1);
  sleep(1);
  }

  for(cnt1=0; cnt1<100; cnt1++){
  fc = (unsigned char) 0x03;
  datalen = 19;
  data[0] = 0xff;
  data[1] = 0xff;
  data[2] = 0xff;
  data[3] = 0xff;
  data[4] = 0xff;
  data[5] = 0xff;
  data[6] = 0xff;
  data[7] = 0xff;
  data[8] = 0xff;
  data[9] = 0xff;
  data[10] = 0xff;
  data[11] = 0xff;
  data[12] = 0xff;
  data[13] = 0xff;
  data[14] = 0xff;
  data[15] = 0xff;
  data[16] = 0xff;
  data[17] = 0xff;
  data[18] = 0xff;
  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt1);
  sleep(1);
  }

  //fc = 0x04 Read Input Registers, not implement excode = 01
  fc = 0x04;
  for(cnt1=0; cnt1<100; cnt1++){
  len = 19;
  data[0] = 0x00;
  data[1] = 0x00;
  data[2] = 0x00;
  data[3] = 0x00;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  data[8] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;
  data[12] = 0x00;
  data[13] = 0x00;
  data[14] = 0x00;
  data[15] = 0x00;
  data[16] = 0x00;
  data[17] = 0x00;
  data[18] = 0x00;

  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);

  freepdu(pdu);
  printf("number is %d\n", cnt1);
  sleep(1);
  }
  
   for(cnt1=0; cnt1<100; cnt1++){
  fc = (unsigned char) 0x04;
  datalen = 19;
  data[0] = 0xff;
  data[1] = 0xff;
  data[2] = 0xff;
  data[3] = 0xff;
  data[4] = 0xff;
  data[5] = 0xff;
  data[6] = 0xff;
  data[7] = 0xff;
  data[8] = 0xff;
  data[9] = 0xff;
  data[10] = 0xff;
  data[11] = 0xff;
  data[12] = 0xff;
  data[13] = 0xff;
  data[14] = 0xff;
  data[15] = 0xff;
  data[16] = 0xff;
  data[17] = 0xff;
  data[18] = 0xff;
  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);

  freepdu(pdu);
  printf("number is %d\n", cnt1);
  sleep(1);
  }

  //fc = 0x18, read FIFO
  fc = 0x18;
  for(cnt1=0; cnt1<100; cnt1++){
  len = 19;
  data[0] = 0x00;
  data[1] = 0x00;
  data[2] = 0x00;
  data[3] = 0x00;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  data[8] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;
  data[12] = 0x00;
  data[13] = 0x00;
  data[14] = 0x00;
  data[15] = 0x00;
  data[16] = 0x00;
  data[17] = 0x00;
  data[18] = 0x00;

  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt1++);
  sleep(1);
  } 

   for(cnt1=0; cnt1<100; cnt1++){
  fc = (unsigned char) 0x18;
  datalen = 19;
  data[0] = 0xff;
  data[1] = 0xff;
  data[2] = 0xff;
  data[3] = 0xff;
  data[4] = 0xff;
  data[5] = 0xff;
  data[6] = 0xff;
  data[7] = 0xff;
  data[8] = 0xff;
  data[9] = 0xff;
  data[10] = 0xff;
  data[11] = 0xff;
  data[12] = 0xff;
  data[13] = 0xff;
  data[14] = 0xff;
  data[15] = 0xff;
  data[16] = 0xff;
  data[17] = 0xff;
  data[18] = 0xff;

  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt1++);
  sleep(1);
  }
 }
}