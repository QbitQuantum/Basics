int main(void){

	/* I searched for this topic and found no real leads so i looked it up.
	 * Opening the serial port
	 * First point is to open a connection. Before opening any connection several informations must be acquired.
	 * 
	 * The name of the serial port.(Usually COM1-COM6 )
	 * The direction of communication.
	 * (It is possible to set the communication to an asynchronic mode but it is far mor complex and unintuitive than the synchronic mode used here)
	 */

	LPCSTR portname = "COM4";
	DWORD  accessdirection =GENERIC_READ | GENERIC_WRITE;
	HANDLE hSerial = CreateFile(portname,
		accessdirection,
		0,
		0,
		OPEN_EXISTING,
		0,
		0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		//call GetLastError(); to gain more information
		printf("Error 1\n");
	}
	
	/*
	 * After opening the port further settings like Baudrate, Byte size, the number of stopbits and the Parity need to be set.
	 */
	 
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		 //could not get the state of the comport
	}
	dcbSerialParams.BaudRate=9600;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	if(!SetCommState(hSerial, &dcbSerialParams)){
		 //analyse error
		 printf("Error 2\n");
	}	
	
	/* Finally timeouts need to be set so that the program does not hang up when receiving nothing. */
	COMMTIMEOUTS timeouts={0};
	timeouts.ReadIntervalTimeout=50;
	timeouts.ReadTotalTimeoutConstant=50;
	timeouts.ReadTotalTimeoutMultiplier=10;
	timeouts.WriteTotalTimeoutConstant=50;
	timeouts.WriteTotalTimeoutMultiplier=10;
	if(!SetCommTimeouts(hSerial, &timeouts)){
		//handle error
		 printf("Error 3\n");
    }
	
	{
		uint8_t symbol = 'A';
		for(symbol = 'A'; symbol <= 'Z'; ++symbol){
			(void)writeToSerialPort(hSerial, &symbol, 1);
		}
	}
	
	/* Closing: when the serial port is not longer needed, it can be freed by closing the associated handle. */
	CloseHandle(hSerial);
	
	printf("Hello\n");
	
	
} /* main */