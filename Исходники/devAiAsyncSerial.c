/* initialize the epics record and the hardware */
static long dsetInit_devAiAsyncSerial(aiRecord *pai)
{
  CONTEXT *p_myContext;
  CALLBACK *p_myCallback;	
  char p_writeBuffer[BUFLEN];
  char p_readBuffer[BUFLEN];
  int myPrimaryAddress;
  int myPortNumber;
  int myParity;
  int myNumberOfDataBits;
  int myNumberOfStopBits;
  int myBaudRate;
  char p_myCommand[BUFLEN];

  #ifdef DEBUG1
  packageInfo();	
  printf(__FILE__ "[%d] -> %s (%s)\n", __LINE__, __func__, pai->name);
  #endif

				/* Parse the db file paramters		*/
				/* and set the value of key variables	*/
  if(sscanf(pai->inp.value.instio.string,
	 "spn=%d pad=%d br=%d nodb=%d p=%d nosb=%d c=%[^\n]",
	&myPortNumber, &myPrimaryAddress, &myBaudRate, 
	&myNumberOfDataBits, &myParity, &myNumberOfStopBits, p_myCommand)!=7) {
    printf( __FILE__ "[%d] Error: Couldn't parse the parameters correctly!", 
		    __LINE__ );
    printf( __FILE__ "[%d] >%s<!", __LINE__, pai->inp.value.instio.string );
    sleep(SLEEPTIME_ERROR);
    return(ERROR);
  } /* end_of_if */

  initSerialPort2(myPortNumber);
  setBaudRate2(myPortNumber,myBaudRate);
  setNumberOfDataBits2(myPortNumber,myNumberOfDataBits);
  setParity2(myPortNumber,myParity);
  setFlowControl2(myPortNumber,NO_FLOW_CONTROL); /* Required for this dev */
  setNumberOfStopBits2(myPortNumber,myNumberOfStopBits);

  #ifdef DEBUG2
  printf(__FILE__ "[%d] portNumber       = %d\n", 
		__LINE__, myPortNumber);
  printf(__FILE__ "[%d] primaryAddress   = %d\n", 
		__LINE__, myPrimaryAddress);
  printf(__FILE__ "[%d] baudRate         = %d\n", 
		__LINE__, getBaudRate2(myPortNumber));
  printf(__FILE__ "[%d] numberOfDataBits = %d\n",
		__LINE__, getNumberOfDataBits2(myPortNumber));
  printf(__FILE__ "[%d] parity           = %d\n", 
		__LINE__, getParity2(myPortNumber));
  printf(__FILE__ "[%d] numberOfStopBits = %d\n",
		__LINE__, getNumberOfStopBits2(myPortNumber));
  printf(__FILE__ "[%d] p_myCommand      = >%s<\n", 
		 __LINE__, p_myCommand); 
  #endif

  if (lockSerialPort2(myPortNumber,LOCK, pai->name)<=ERROR) {
	printf( __FILE__ "[%d] Error: Couldn't lock serial port (%s)\n",
			__LINE__, getSerialPortName2(myPortNumber));
	sleep(SLEEPTIME_ERROR);
	return(ERROR);
  }
  				/* Disable front panel 			*/
				/* This operation should work if 	*/
				/* communication parameters are ok	*/
  strcpy(p_writeBuffer,"XFRONT");
  strcat(p_writeBuffer,TERMINATOR); 

  openSerialPort2(myPortNumber);
  if (writeSerialPort2(myPortNumber, p_writeBuffer ) <= ERROR) {
	printf( __FILE__ "[%d] Error: Couldn't write on %s\n",
			__LINE__, getSerialPortName2(myPortNumber));
	sleep(SLEEPTIME_ERROR);
	return(ERROR);
  }
  usleep(USLEEPTIME_WRITE);

  memset(p_readBuffer,0,BUFLEN);

  if (readSerialPort2(myPortNumber, p_readBuffer, BUFLEN) <= ERROR) {
	printf( __FILE__ "[%d] Error: Couldn't read on %s\n",
			__LINE__, getSerialPortName2(myPortNumber));
	sleep(SLEEPTIME_ERROR);
	return(ERROR);
  }
  usleep(USLEEPTIME_READ);
  if (lockSerialPort2(myPortNumber,UNLOCK, pai->name)<=ERROR) {
    printf ( __FILE__ "Error");
    sleep(SLEEPTIME_ERROR);
    return(ERROR);
  }


  p_myCallback=(CALLBACK *)calloc(1,sizeof(CALLBACK));
  callbackSetCallback(myCallback_devAiAsyncSerial,p_myCallback);
  callbackSetUser(pai,p_myCallback);
 
  p_myContext=(CONTEXT *)calloc(1,sizeof(CONTEXT));
  p_myContext->portNumber=myPortNumber;
  p_myContext->p_callback=p_myCallback;
  p_myContext->primaryAddress=myPrimaryAddress;
  strncpy(p_myContext->p_command, p_myCommand, BUFLEN);
  pai->dpvt=(void *)p_myContext;

				/* Check acknowledgement		*/
  if (strncmp(p_readBuffer,"OK",2)!=0) {
      printf( __FILE__ "[%d] Error: Couldn't communicate with  %s\n",
		      __LINE__, pai->name);
      printf( __FILE__ "[%d] Check configuration parameters?\n", __LINE__);
      return(ERROR);
  }

  #ifdef DEBUG1
  printf( __FILE__ "[%d] <- %s\n", __LINE__, __func__);
  #endif

  return(SUCCESS);

} /* end init_press_record() */