void WlanStationMode( void *pvParameters )
{
    int iTestResult = 0;
    unsigned long ulIP = 0;
    unsigned long ulSubMask = 0;
    unsigned long ulDefaultGateway = 0;
    unsigned long ulDNSServer = 0;
    unsigned char ucDHCP = 0;
    char cMode;
    char* buff="hhhhhh\n\r";
    unsigned char currentMacAddress[SL_MAC_ADDR_LEN];
    
    //UART_PRINT(" in WlanStationMode  \n\r"); 
    
/*  for(int a = 0; a<5; ++a){
    Z_DelayS(30);
    *buff=a+'0';
    UART_PRINT(buff);   
    }
 */   
    
    

    
    
    
    
    
    
 
    
    
  char deviceRole = ROLE_STA;  
    
  deviceRole = sl_Start(NULL,NULL,InitCallback);
 /* deviceRole = sl_Start(NULL,NULL,NULL);
    
    if(deviceRole < 0 ){
      UART_PRINT("sl_Start error  \n\r");
      return;
    }
    else if(deviceRole == ROLE_STA)
        UART_PRINT("in station mode  \n\r"); 
          else{
            UART_PRINT("in wrong mode  \n\r"); 
            return;
          }
 */     
    
 /*  if((cMode = sl_Start(NULL,NULL,NULL)) != ROLE_STA){
      UART_PRINT("hellow  \n\r"); 
      
      *buff=cMode+'0';
      UART_PRINT(buff);
      *buff=ROLE_STA+'0';
      UART_PRINT(buff);
      
 //     SL_WLAN_SET_MODE_STA();
    }
     
    UART_PRINT("hellow i am in station mode now \n\r"); 
    
  */   
    
 while(!g_uiSimplelinkstarted)
 {
        //looping till simplelink starts
  Z_DelayS(1);
  // ; 
   UART_PRINT("i am starting now \n\r"); 
 } 
             
   UART_PRINT("i am started   \n\r");          
             
    // Connecting to WLAN AP - Set with static parameters defined at the top
	// After this call we will be connected and have IP address */
    WlanConnect();
  

  
    
   UART_PRINT("i'm connected! \n\r"); 
    
    //get mac addr from s-flash
    
    SL_MAC_ADDR_GET(currentMacAddress);   
    Z_MACDispaly(currentMacAddress);
    
    
    SL_STA_IPV4_ADDR_GET(&ulIP,&ulSubMask,&ulDefaultGateway,&ulDNSServer,
                       &ucDHCP);
    
    
    
    Z_IPDispaly(&ulIP);
    MyIP=ulIP;
    Z_IPDispaly(&ulSubMask);
    Z_IPDispaly(&ulDefaultGateway);

    
    
    
    /*
    
    UNUSED(ulIP);
    UNUSED(ulSubMask);
    UNUSED(ulDNSServer);
    UNUSED(ucDHCP);
    */
    
   // iTestResult = PingTest(ulDefaultGateway);
  //  UNUSED(iTestResult);
    
 //BsdTcpServer(PORT_NUM); 
    
 //mqtt_pub();
    UART_PRINT("WlanStationMode\r\n"); 
    vTaskDelete(NULL);
    UART_PRINT("WlanStationMode\r\n"); 
 return;
 
 
    
    
    
    
    
}