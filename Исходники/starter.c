int main(void)
{
    UINT8  IsDHCP = 0;
    int32_t i32CommandStatus;
    _NetCfgIpV4Args_t ipV4;
		SlSockAddrIn_t    Addr; 
		UINT16            AddrSize = 0; 
		INT16             SockID = 0; 
		UINT32            data; 
		long x = 0; //counter
    unsigned char len = sizeof(_NetCfgIpV4Args_t);
    int Status = 0;
    /* Stop WDT */
    stopWDT();
    /* Initialize the system clock of MCU */
    initClk();
		Board_Init();       // initialize LaunchPad I/O and PD1 LED
    ConfigureUART();    // Initialize the UART.
    UARTprintf("Section 11.4 IoT example, Volume 2 Real-time interfacing\n");
    UARTprintf("This application is configured to generate text\n");
    UARTprintf("  and send UDP packets to IP: %d.%d.%d.%d  Port: %d\n\n",
      SL_IPV4_BYTE(IP_ADDR,3), SL_IPV4_BYTE(IP_ADDR,2), 
      SL_IPV4_BYTE(IP_ADDR,1), SL_IPV4_BYTE(IP_ADDR,0),PORT_NUM);
		//added code from the powerpoint slide
    /* Initializing the CC3100 device */
    sl_Start(0, 0, 0);
    /* Connecting to WLAN AP - Set with static parameters defined at the top
       After this call we will be connected and have IP address */
    WlanConnect();
    /* Read the IP parameter */
    sl_NetCfgGet(SL_IPV4_STA_P2P_CL_GET_INFO,&IsDHCP,&len,(unsigned char *)&ipV4);
    UARTprintf("This node is at IP: %d.%d.%d.%d\n", SL_IPV4_BYTE(ipV4.ipV4,3), SL_IPV4_BYTE(ipV4.ipV4,2), SL_IPV4_BYTE(ipV4.ipV4,1), SL_IPV4_BYTE(ipV4.ipV4,0));
    Addr.sin_family = SL_AF_INET;
    Addr.sin_port = sl_Htons((UINT16)PORT_NUM);
    Addr.sin_addr.s_addr = sl_Htonl((UINT32)IP_ADDR);
    AddrSize = sizeof(SlSockAddrIn_t);
    SockID = sl_Socket(SL_AF_INET,SL_SOCK_DGRAM, 0);
    // Loop forever waiting  for commands from PC...
    //
    while(1)
    {
        // Print prompt for user.
        UARTprintf("\n>");
        // Peek to see if a full command is ready for processing.
        while(UARTPeek('\r') == -1)
						LED_On();
            // Approximately 1 millisecond delay.
            ROM_SysCtlDelay(ROM_SysCtlClockGet() / 3000);

        }
        // A '\r' was detected so get the line of text from the receive buffer.
		while(Status >= 0){
      UARTprintf("\nSending a UDP packet ...\n");
		
			UARTgets(g_cInput,sizeof(g_cInput)); //this function receives the input from the Putty and places it in a string

			
			
			//DO NOT CHANGE ANYTHING ABOVE THIS COMMENT
			
			//WHAT WE NEED TO DO:
			//work with the g_cInput to get the array of letters typed into the Putty
			//then send that Array using UARTprintf
			uBuf[0] = ATYPE;   // defines this as an analog data type
			uBuf[1] = '='; 
			data = 1000;

			Int2Str(data,(char*)&uBuf[2]); // [2] to [7] is 6 digit number
      UARTprintf(" %s ",uBuf); //this line sends a string to the receiver
      //the above 5 lines print out a = 1000;
			//everything below this is just error cases
			if( SockID < 0 ){
        UARTprintf("SockIDerror ");
        Status = -1; // error
      }else{
        LED_Toggle();
        Status = sl_SendTo(SockID, uBuf, BUF_SIZE, 0,
                           (SlSockAddr_t *)&Addr, AddrSize);
        if( Status <= 0 ){
          sl_Close(SockID);
          UARTprintf("SockIDerror %d ",Status);
        }else{
          UARTprintf("ok");
        }
      }
      ROM_SysCtlDelay(ROM_SysCtlClockGet() / 100); // 10ms
			LED_Off();
		}
   }