/*-------------------------------------------
| Name:setRs2322
| Description:
| Parameters:
| Return Type:
| Comments:
| See:
---------------------------------------------*/
int setRs2322(uart2_config* config){
   /*
   COMMCONFIG  commconfig;
   DWORD       dwSize=sizeof(COMMCONFIG);
   char buffer[256]={0};
   sprintf(buffer,"%s: baud=%d parity=%c data=%d stop=%d",USE_COM,
      config->speed,
      config->parity,
      config->data,
      config->stop);

   if(!GetCommConfig(hCom,&commconfig,&dwSize))
      return -1;

   BuildCommDCB(buffer,&commconfig.dcb);

   //CommConfigDialog(USE_COM,NULL,&commconfig);

   if(!SetCommConfig(hCom,&commconfig,dwSize))
      return -1;

   printf("com cfg: %s\n",buffer);

   memcpy(&current_config,config,sizeof(uart2_config));
   */

   COMMCONFIG commconfig;
   DWORD dwSize=sizeof(COMMCONFIG);
   char buffer[256]={0};
   DCB dcb={0};

   COMMTIMEOUTS NewTimeouts;           // Serial port new timeouts
   COMMTIMEOUTS OldTimeouts;           // Serial port old timeouts

   sprintf(buffer,"%s: baud=%d parity=%c data=%d stop=%d",USE_COM,
           config->speed,
           config->parity,
           config->data,
           config->stop);

   if(!GetCommConfig(hCom,&commconfig,&dwSize))
      return -1;

   BuildCommDCB(buffer,&commconfig.dcb);

   //CommConfigDialog(USE_COM,NULL,&commconfig);

   if(!SetCommConfig(hCom,&commconfig,dwSize))
      return -1;

   // Get default DCB and initialize
   if(!GetCommState( hCom, &dcb))
   {
      CloseHandle( hCom );
      return -1;
   }
   else
   {
      dcb.fOutxCtsFlow = FALSE;
      dcb.fOutxDsrFlow = FALSE;
      dcb.fDtrControl = DTR_CONTROL_ENABLE;//DTR_CONTROL_DISABLE;            // DTR ON when device open (+12V) in order to power Optical link with DTR
      dcb.fRtsControl = RTS_CONTROL_ENABLE;//RTS_CONTROL_DISABLE;            // RTS OFF when device open (-12V) in order to power Optical link with RTS
      dcb.fDsrSensitivity = FALSE;
//	    dcb.fTXContinueOnXoff = false;
      dcb.fTXContinueOnXoff = TRUE;
      dcb.fNull = FALSE;
   }

   dcb.fOutX = FALSE;
   dcb.fInX = FALSE;
   dcb.fErrorChar = FALSE;
   dcb.fAbortOnError = FALSE;
   dcb.XonLim = 0;     //32;
   dcb.XoffLim = 0;     //32;
   dcb.XonChar =  40;
   dcb.XoffChar = 41;
   dcb.ErrorChar = 0;
   dcb.EofChar = 0;
   dcb.EvtChar = 0;             // '\n' is the last character of a Modbus frame ; this character will be the event for retreiving the receive buffer
   dcb.wReserved = 0;

   // Set the new state of the serial port.
   if(!SetCommState( hCom, &dcb))
   {
      CloseHandle( hCom );
      return -1;
   }

   // Save current timeouts
   GetCommTimeouts(hCom, &OldTimeouts);

   // Set new read timeout
   memcpy((void *)&NewTimeouts, (const void *)&OldTimeouts, sizeof(COMMTIMEOUTS));

   NewTimeouts.ReadIntervalTimeout = 0;
   NewTimeouts.ReadTotalTimeoutMultiplier = 0;
   NewTimeouts.ReadTotalTimeoutConstant = 0; // Timeout is expressed in milliseconds

   SetCommTimeouts (hCom, &NewTimeouts);

   //
   printf("com cfg: %s\n",buffer);

   memcpy(&current_config,config,sizeof(uart2_config));


   return 0;
}