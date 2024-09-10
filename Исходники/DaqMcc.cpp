//-----------------------------------------------------------------------------
//	sends command down the serial port, puts the reply into response
//-----------------------------------------------------------------------------
static bool SendCommand(void) {

	if (!serialRunning)	{						// no comms until it's all been set up
		ERROR_MESSAGE_EXT(_T("DAQ error - serial not running\r\n"));
		return false;
	}

	WaitForSerial();

	DWORD nBytes;
	serialBusy = true;
	bool ok = true;

	strcat_s(command, COMMAND_LENGTH, "\r\n");		// append "\r\n"

	// send the command
	WriteFile(hSerialDaq, command, strlen(command), &nBytes, NULL);
	ok = (nBytes == strlen(command));

	if (ok) {
		// get the response a byte at a time until I get '\n'
		int i;
		for (i = 0; i < RESPONSE_LENGTH; i++)  {
			do {
				ReadFile(hSerialDaq, response + i, 1, &nBytes, NULL);
			} while (nBytes == 0);

/*			ReadFile(hSerialDaq, response + i, 1, &nBytes, NULL);
			// ReadFile returns true if there's a timeout
			if (!nBytes) 								// there was a timeout
				break;*/

			if (response[i] == '\n') {					// success
				ok = true;
				break;
			}
		}
		response[i + 1] = '\0';							// terminate string
	} else
		ERROR_MESSAGE_EXT(_T("SendCommand error\r\n"));


	// report any comms errors
	if (!ok) {
		serialRunning = false;
		switch (command[0]) {
			case '#':
				ERROR_MESSAGE_EXT(_T("Housekeeping board comms error\r\n"));
				break;
			case '*':
				ERROR_MESSAGE_EXT(_T("Analog board comms error\r\n"));
				break;
			case '$':
				ERROR_MESSAGE_EXT(_T("Pump drive board comms error\r\n"));
				break;
		}
	}

	serialBusy = false;
	return ok;
}