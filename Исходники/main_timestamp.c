//****************************************************************************
//                            MAIN FUNCTION
//****************************************************************************
void main()
{
    long lRetVal = 0;
    char data[BUF_SIZE];
    char sent_data[BUF_SIZE];
    unsigned char highByte, lowByte;
    int i;

    unsigned long tempStartTimeStamp, tempStopTimeStamp;

    memset(sent_data, 0, 10);
    // Board Initialization
    BoardInit();

    // Configure the pinmux settings for the peripherals exercised
    PinMuxConfig();

    // Initialize the PWM outputs on the board
    InitServos();

    // Initialize the sensor ADC
    InitSensorADC();

    // Configuring UART
    InitTerm();

    // Display banner
    DisplayBanner(APPLICATION_NAME);

    // Connect to WIFI using default info
    //WlanConnect(NULL, NULL, NULL);
    WlanConnect("Nagui's Network", "SL_SEC_TYPE_WPA", "19520605");

    // Setup the TCP Server Socket
    BsdTcpServerSetup(PORT_NUM);

    // Recieve Data
    while (lRetVal >= 0)
    {
    	lRetVal = BsdTcpServerReceive(data);

		//SysTickPeriodSet(800000000);				// test
		//SysTickEnable();						// test
    	Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_A, 0);
    	Timer_IF_Start(TIMERA0_BASE, TIMER_A, MILLISECONDS_TO_TICKS(2000));
		//tempStartTimeStamp = SysTickValueGet();		// test
    	tempStartTimeStamp = Timer_IF_GetCount(TIMERA0_BASE, TIMER_A);

    	for (i = 0; i<NUM_SERVOS; i++)
    	{
    		MoveServo((unsigned char)data[i], (enum Servo_Joint_Type)i);
    		UART_PRINT("%d", (unsigned int) data[i]);
    	}

    	for (i = 0; i< NUM_SENSORS; i++)
    	{
        	//UnsignedShort_to_UnsignedChar(GetSensorReading((enum Fingertip_Sensor_Type)i), &highByte, &lowByte);
    		UnsignedShort_to_UnsignedChar(GetSensorReading(SENSOR_FINGER_INDEX), &highByte, &lowByte);
        	sent_data[i*2] = (char)highByte;
        	sent_data[i*2+1] = (char)lowByte;
    	}
    	//tempStopTimeStamp = SysTickValueGet();					// test
    	tempStopTimeStamp = Timer_IF_GetCount(TIMERA0_BASE, TIMER_A);
    	lRetVal = BsdTcpServerSend(sent_data, 10);
    	UART_PRINT("timestamp start: %lu\n\r", tempStartTimeStamp);	//test
    	UART_PRINT("timestamp stop: %lu\n\r", tempStopTimeStamp);	//test
    	UART_PRINT("Sent 10 bytes to client.\n\r");

    }
    UART_PRINT("Exiting Application ...\n\r");

    // power of the Network processor
    lRetVal = sl_Stop(SL_STOP_TIMEOUT);

}