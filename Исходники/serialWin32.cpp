	//------------------------------------------------------------------------------------------------------------------
	SerialWin32::SerialWin32(const char* _port, unsigned _baudRate){
		// Enforce correct data
		assert(nullptr != _port && '\0' != _port[0]);

		openPort(_port);
		setBaudRate(_baudRate);
	}