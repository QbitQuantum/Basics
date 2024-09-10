int main(void){
  UINT8             IsDHCP = 0;
  _NetCfgIpV4Args_t ipV4;
  SlSockAddrIn_t    Addr;
  SlSockAddrIn_t    LocalAddr;
  UINT16            AddrSize = 0;
  INT16             SockID = 0;
  INT16             Status = 1;  // ok
  UINT32            data;
  unsigned char     len = sizeof(_NetCfgIpV4Args_t);
  stopWDT();        // Stop WDT 
  initClk();        // PLL 50 MHz, ADC needs PPL active
  Board_Init();     // initialize LaunchPad I/O 
  ConfigureUART();  // Initialize the UART.
  UARTprintf("Section 11.4 IoT example, Volume 2 Real-time interfacing\n");
  UARTprintf("This node is configured to receive UDP packets\n");
  UARTprintf("This node should be at IP: %d.%d.%d.%d  Port: %d\n\n",
      SL_IPV4_BYTE(IP_ADDR,3), SL_IPV4_BYTE(IP_ADDR,2), 
      SL_IPV4_BYTE(IP_ADDR,1), SL_IPV4_BYTE(IP_ADDR,0),PORT_NUM);
  ST7735_InitR(INITR_REDTAB);
  ST7735_OutString("Internet of Things\n");
  ST7735_OutString("Embedded Systems\n");
  ST7735_OutString("Vol. 2, Valvano");
  ST7735_PlotClear(0,4095);  // range from 0 to 4095
  while(1){
    sl_Start(0, 0, 0); /* Initializing the CC3100 device */
    /* Connecting to WLAN AP - Set with static parameters defined at the top
       After this call we will be connected and have IP address */
    WlanConnect();   // connect to AP
    /* Read the IP parameter */
    sl_NetCfgGet(SL_IPV4_STA_P2P_CL_GET_INFO,&IsDHCP,&len,(unsigned char *)&ipV4);
    UARTprintf("This node is at IP: %d.%d.%d.%d\n", SL_IPV4_BYTE(ipV4.ipV4,3), SL_IPV4_BYTE(ipV4.ipV4,2), SL_IPV4_BYTE(ipV4.ipV4,1), SL_IPV4_BYTE(ipV4.ipV4,0));
    while(Status > 0){
      UARTprintf("\nReceiving a UDP packet ...");

      LocalAddr.sin_family = SL_AF_INET;
      LocalAddr.sin_port = sl_Htons((UINT16)PORT_NUM);
      LocalAddr.sin_addr.s_addr = 0;
      AddrSize = sizeof(SlSockAddrIn_t);
      SockID = sl_Socket(SL_AF_INET,SL_SOCK_DGRAM, 0);     
      if( SockID < 0 ){
        UARTprintf("SockIDerror\n");
        Status = -1; // error
      }else{
        Status = sl_Bind(SockID, (SlSockAddr_t *)&LocalAddr, AddrSize);
        if( Status < 0 ){
          sl_Close(SockID); 
          UARTprintf("Sock Bind error\n");
        }else{
          Status = sl_RecvFrom(SockID, uBuf, BUF_SIZE, 0,
                  (SlSockAddr_t *)&Addr, (SlSocklen_t*)&AddrSize );
          if( Status <= 0 ){
            sl_Close(SockID);
            UARTprintf("Receive error %d ",Status);
          }else{
            LED_Toggle();
            sl_Close(SockID);
            UARTprintf("ok %s ",uBuf);
            if((uBuf[0]==ATYPE)&&(uBuf[1]== '=')){ int i,bOk; uint32_t place;
              data = 0; bOk = 1;
              i=4;  // ignore possible negative sign
              for(place = 1000; place; place = place/10){
                if((uBuf[i]&0xF0)==0x30){ // ignore spaces
                  data += place*(uBuf[i]-0x30);
                }else{
                  if((uBuf[i]&0xF0)!= ' '){
                    bOk = 0;
                  }
                }
                i++;
              }
              if(bOk){
                ST7735_PlotLine(data);
                ST7735_PlotNextErase(); 
              }
            }
          }
        }
      }
      ROM_SysCtlDelay(ROM_SysCtlClockGet() / 25); // 120ms
    }
  }
}