void CKerrControl::InitControllers()
{
	// Kerr controller require the ID of each Servo sub-controller to be initialized at startup
	// All controllers start with ID=0, but only the first will respond.
	// So we change first one to 1, and the second to 2.

	/* 
	From the Kerr "Arduino-Servo SC" user's manual: PicSrvSC.pdf (page 6):
	1. On power-up, all modules assume a default address of 0x00, and each will set its ADDR_OUT
	signal HIGH. Furthermore, a module’s communications will be disabled completely until its
	ADDR_IN signal goes LOW. If the ADDR_OUT and ADDR_IN signals are daisy-chained as
	described above, all modules will be disabled except for the module furthest from the host.
	2. The host starts by sending a Set Address command to module 0, changing its address to a value of
	1. A side affect of the Set Address command is that the module will lower the its ADDR_OUT
	signal.
	3. At this point, the next module in line is enabled with an address of 0. The host then sends a
	command to module 0 to change its address to a value of 2.
	4. This process is continued until all modules have been assigned unique addresses.
	*/

	if( m_ControllerIDsInitialized )
	{
		return; // only do once!
	}
	m_ControllerIDsInitialized = TRUE;

	// Send a bunch of zeros to get the Kerr control synchronized
	m_KerrCmd.ID = 0;			// Address of Servo to access use 0 for initial start-up
	m_KerrCmd.Command = 0;			
	m_KerrCmd.Data[0] = 0;
	m_KerrCmd.Data[1] = 0;
	m_KerrCmd.Data[2] = 0;
	m_KerrCmd.Data[3] = 0;
	m_KerrCmd.Data[4] = 0;
	m_KerrCmd.Data[5] = 0;
	m_KerrCmd.Data[6] = 0;
	m_KerrCmd.Data[7] = 0;
	m_KerrCmd.Data[8] = 0;
	m_KerrCmd.Data[9] = 0;
	m_KerrCmd.Data[10] = 0;
	m_KerrCmd.Data[11] = 0;
	m_KerrCmd.Data[12] = 0;
	m_KerrCmd.Data[13] = 0;
	m_KerrCmd.Data[14] = 0;
	m_KerrCmd.Data[15] = 0;
	SendCmd(16,0, FALSE);	// no response expected, just flushing the port


	m_KerrCmd.ID = 0;			// Address of Servo to access use 0 for initial start-up
	m_KerrCmd.Command = 0x0E;	// Send NOP to just get a status back (which is ignored)		
	SendCmd(0, 0, FALSE);


	m_KerrCmd.ID = 0xFF;			// Address of Servo - FF = all servos (default group)
	m_KerrCmd.Command = KERR_CMD_HARD_RESET;	// High Nibble contains number of Data Bytes		
	SendCmd(0,0, FALSE);	// No response to Reset command

	Sleep(100);

	// Purge the comm port input and output of junk
	if( (INVALID_HANDLE_VALUE != g_hKerrServoCommPort)  && (SIMULATED_SIO_HANDLE != g_hKerrServoCommPort) )
	{
		if( !PurgeComm(g_hKerrServoCommPort, (PURGE_TXCLEAR | PURGE_RXCLEAR)) )
		{
			ROBOT_ASSERT(0);	// Purge failed.  Need to call GetLastError().
		}
	}

	// Set the first servo controller ID
	m_KerrCmd.ID = 0;			// Address of Servo to access use 0 for initial start-up
	m_KerrCmd.Command = KERR_CMD_SET_ADDRESS + 0x20;	// High Nibble contains number of Data Bytes		
	m_KerrCmd.Data[0] = KERR_ARM_MOTOR_ID_RIGHT;		// Individual Address = 1
	m_KerrCmd.Data[1] = 0xFF;	// No Group Address
	SendCmd(2);

	Sleep(100);
	
	// Set the second servo controller ID
	m_KerrCmd.ID = 0;			// Address of Servo to access use 0 for initial start-up
	m_KerrCmd.Command = KERR_CMD_SET_ADDRESS + 0x20;	// High Nibble contains number of Data Bytes		
	m_KerrCmd.Data[0] = KERR_ARM_MOTOR_ID_LEFT;		// Individual Address = 2
	m_KerrCmd.Data[1] = 0xFF;	// No Group Address
	SendCmd(2);

	
// Set the Amplifier Gain

	m_KerrCmd.ID = KERR_ARM_MOTOR_ID_RIGHT;			// Address of Servo
	m_KerrCmd.Command  = 0xF6;			
	m_KerrCmd.Data[0]  = 0x64;
	m_KerrCmd.Data[1]  = 0x00;
	m_KerrCmd.Data[2]  = 0xE8;
	m_KerrCmd.Data[3]  = 0x03;
	m_KerrCmd.Data[4]  = 0x00;
	m_KerrCmd.Data[5]  = 0x00;
	m_KerrCmd.Data[6]  = 0x00;
	m_KerrCmd.Data[7]  = 0x00;
	m_KerrCmd.Data[8]  = 0xFF;
	m_KerrCmd.Data[9]  = 0x00;
	m_KerrCmd.Data[10] = 0xA0;
	m_KerrCmd.Data[11] = 0x0F;
	m_KerrCmd.Data[12] = 0x01;
	m_KerrCmd.Data[13] = 0x01;
	m_KerrCmd.Data[14] = 0x01;
	SendCmd(15);

	m_KerrCmd.ID = KERR_ARM_MOTOR_ID_LEFT;			// Address of Servo
	m_KerrCmd.Command  = 0xF6;			
	m_KerrCmd.Data[0]  = 0x64;
	m_KerrCmd.Data[1]  = 0x00;
	m_KerrCmd.Data[2]  = 0xE8;
	m_KerrCmd.Data[3]  = 0x03;
	m_KerrCmd.Data[4]  = 0x00;
	m_KerrCmd.Data[5]  = 0x00;
	m_KerrCmd.Data[6]  = 0x00;
	m_KerrCmd.Data[7]  = 0x00;
	m_KerrCmd.Data[8]  = 0xFF;
	m_KerrCmd.Data[9]  = 0x00;
	m_KerrCmd.Data[10] = 0xA0;
	m_KerrCmd.Data[11] = 0x0F;
	m_KerrCmd.Data[12] = 0x01;
	m_KerrCmd.Data[13] = 0x01;
	m_KerrCmd.Data[14] = 0x01;
	SendCmd(15);


	// In case the arm was up when reset, the counter is now not at zero
	// so, reset it to get it close enough to allow home calibration to work right
	m_KerrCmd.ID = KERR_ARM_MOTOR_ID_RIGHT;	// First Arm
	m_KerrCmd.Command = KERR_CMD_RESET_POS;	// High Nibble contains number of Data Bytes (none)		
	SendCmd(0);

	m_KerrCmd.ID = KERR_ARM_MOTOR_ID_LEFT;	// Second Arm
	m_KerrCmd.Command = KERR_CMD_RESET_POS;	// High Nibble contains number of Data Bytes (none)		
	SendCmd(0);

}