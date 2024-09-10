void CRC_main
(
	uint_32 initial_data
)
{
  uint_32  crc_error=0;
  uint_32  poly;
  uint_32  tot;
  uint_32  totr;
  uint_32  fxor;
  uint_32  tcrc;  
  uint_8   gbQuit = 0;
  uint_32  bByteCount;
  uint_8   ch;
  uint_32  seed,crc;
  uint_8   mode = 1;
 
  isCRC16 = 1;
  printf("\n====== CRC Lab ==========\r\n"); 
  do
   {
     if (mode == 1){
            mode = 0;
     			printf("\nPlease select CRC width (16-bit/32-bit):\r\n");
     			printf("1. CRC16\n");
     			printf("2. CRC32\n");
     			printf("select:");
     			do{
     			  ch = fgetc(stdin);
     			}while ((ch != '1') && (ch != '2'));
     			printf("%c\r\n",ch);
     			isCRC16 = !(ch-'1');
     			
     			printf("\r\nPlease select CRC polynomial:\r\n");
     			printf("1. poly = 0x1021 (CRC-CCITT)\r\n");
     			printf("2. poly = 0x8408 (XMODEM)\r\n");
     			printf("3. poly = 0x8005 (ARC)\r\n");
     			printf("4. poly = 0x04C11DB7 (CRC32) \r\n");
     			printf("5. others\r\n");
     			printf("select:");
     			do{
     			  ch = fgetc(stdin); //scanf("%c", &ch);     
     			}while(!((ch < '6') && (ch > '0')));
     			printf("%c\r\n",ch);
     			if(ch == '5')
     			{
     			  printf("Please enter a polynomial in hex format:"); 
     			  poly = Input_Word();
     			}
     			else
     			{
     			  poly = polyTab[ch-'1'];
     			}
     			tcrc = (isCRC16)? 0: 1;                // width of CRC   
     			
     			printf("\r\nPlease select type of Transpose for input:\r\n");
     			printf("1. No Transposition\r\n");
     			printf("2. Only transpose bits in a byte\r\n");
     			printf("3. Transpose both bits and bytes\r\n");
     			printf("4. Only transpose bytes\r\n");
     			printf("select:");
     			do{
     			  ch = fgetc(stdin);
     			}while (!((ch < '5') && (ch > '0')));
     			printf("ch = %c \r\n",ch);
     			tot = ch - '1';
     			
     			printf("\r\nPlease select type of Transpose for Read:\r\n");
     			printf("1. No Transposition\r\n");
     			printf("2. Only transpose bits in a byte\r\n");
     			printf("3. Transpose both bits and bytes\r\n");
     			printf("4. Only transpose bytes\r\n");
     			printf("select:");
     			do{
     			  ch = fgetc(stdin);
     			}while (!((ch < '5') && (ch > '0')));
     			printf("ch = %c\r\n",ch);
     			totr = ch - '1';
     			
     			printf("XOR final checksum (y/n)?");
     			do{
     			  ch = fgetc(stdin);
     			}while ((ch != 'y') && (ch != 'n'));     
     			printf("ch = %c\r\n",ch);
     			fxor = (ch == 'y')? 1: 0;
     			
     			 printf("Please enter seed in hex:");
     			 seed = Input_Word();
     	}		
      printf("\r\nPlease enter an ASCII Message:");
      bByteCount = Input_Message(&strMsg[0]);
      crc_error=CRC_Config(poly,tot,totr,fxor,tcrc);  
      if(isCRC16)
      {
        crc = CRC_Cal_16(seed, &strMsg[0], bByteCount);
        printf("\r\n CRC result = %#04.4x\r\n",(crc & 0x0000FFFFL));
      }
      else
      {
        crc = CRC_Cal_32(seed, &strMsg[0], bByteCount);
        printf("\r\n CRC result = %#08.8x\r\n",crc);        
      }
      printf("Press any key to enter new data...,except 'q' to quit, 'c' to re-configuration !\r\n");
      do
      {
        ch = fgetc(stdin);
      }while( !ch );
      if(ch == 'q')
      {
        gbQuit = 1;
      }           
      if(ch == 'c')
      {
        mode = 1;
      }           
   }while(!gbQuit);
    
  gbQuit = 0;
  printf("Demo is quited!\r\n");
}