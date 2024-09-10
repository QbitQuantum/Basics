/*!
 * Open the specified device at a specified baud and create a new device handle
 * \param[in]	deviceName			Device name / address (COM21 , /dev/ttys0, depending on platform)
 * \param[in]	baudRate			Baudrate to be used
 * \param[out]	pHandle				Device handle returned
 * \return							SBG_NO_ERROR if the device could be oppened properly
 */
SbgErrorCode sbgDeviceOpen(const char *deviceName, uint32 baudRate, SbgDeviceHandle *pHandle)
{
	char errorMsg[256];
	char comPortPath[32];
	COMMTIMEOUTS comTimeOut;
	DCB comState;
	uint32 deviceNum;
	HANDLE hSerialDevice;

	//
	// First check if we have a valid pHandle
	//
	if (pHandle)
	{
		//
		// Extract device number
		//
		if (sscanf_s(deviceName, "COM%i", &deviceNum) == 1)
		{
			//
			// Build our com port path
			//
			sprintf_s(comPortPath, 32, "\\\\.\\COM%i", deviceNum);

			//
			// Init our com port
			//
			hSerialDevice = CreateFile(comPortPath, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hSerialDevice != INVALID_HANDLE_VALUE)
			{
				//
				// Define our device handle
				//
				*pHandle = hSerialDevice;

				//
				// Purge our com port
				//
				if (PurgeComm(hSerialDevice, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
				{
					//
					// Retreives current com state and com timeout
					//
					if ( (GetCommState(hSerialDevice, &comState)) && (GetCommTimeouts(hSerialDevice, &comTimeOut)) )
					{
						//
						// Define common attributes
						//
						comState.BaudRate= baudRate;
						comState.Parity= NOPARITY;
						comState.ByteSize= 8;
						comState.StopBits= ONESTOPBIT;

						//
						// Disable flow control
						//
						comState.fDsrSensitivity = FALSE;
						comState.fOutxCtsFlow = FALSE;
						comState.fOutxDsrFlow = FALSE;
						comState.fOutX = FALSE;
						comState.fInX = FALSE;

						//
						// Define timeout attributes (0 ms read timeout)
						//
						comTimeOut.ReadIntervalTimeout = MAXDWORD;
						comTimeOut.ReadTotalTimeoutMultiplier = 0;
						comTimeOut.ReadTotalTimeoutConstant = 0;

						comTimeOut.WriteTotalTimeoutConstant = 0;
						comTimeOut.WriteTotalTimeoutMultiplier = 0;
						

						//
						// Configure our com port
						//
						if ( (SetCommState(hSerialDevice, &comState)) && (SetCommTimeouts(hSerialDevice, &comTimeOut)) )
						{
							//
							// Wait until our com port has been configured by windows
							//
							sbgSleep(60);

							//
							// Define our COM port buffer size
							//
							if (SetupComm(hSerialDevice, SBG_SERIAL_RX_BUFFER_SIZE, SBG_SERIAL_TX_BUFFER_SIZE))
							{
								//
								// Purge our communication
								//
								return sbgDeviceFlush(hSerialDevice);
							}
							else
							{
								sbgGetWindowsErrorMsg(errorMsg);
								fprintf(stderr, "sbgDeviceOpen: Unable to define buffer size: %s.\n", errorMsg);
							}
						}
						else
						{
							sbgGetWindowsErrorMsg(errorMsg);
							fprintf(stderr, "sbgDeviceOpen: Unable to set com state and/or timeout: %s.\n", errorMsg);
						}
					}
					else
					{
						sbgGetWindowsErrorMsg(errorMsg);
						fprintf(stderr, "sbgDeviceOpen: Unable to retreive com state and/or timeout: %s.\n", errorMsg);
					}
				}
				else
				{
					sbgGetWindowsErrorMsg(errorMsg);
					fprintf(stderr, "sbgDeviceOpen: Unable to purge com port %i: %s.\n", deviceNum, errorMsg);
				}

				//
				// Close our device if only some part has been initialised
				//
				sbgDeviceClose(hSerialDevice);
			}
			else
			{
				//
				// We have an invalid device handle
				//
				*pHandle = SBG_INVALID_DEVICE_HANDLE;
				
				sbgGetWindowsErrorMsg(errorMsg);
				fprintf(stderr, "sbgDeviceOpen: Unable to open com port %i: %s\n", deviceNum, errorMsg);
			}

			return SBG_ERROR;
		}
		else
		{
			fprintf(stderr, "sbgDeviceOpen: Invalid deviceName: %s\n", deviceName);
			return SBG_INVALID_PARAMETER;
		}
	}
	else
	{
		fprintf(stderr, "sbgDeviceOpen: pHandle == NULL for deviceName: %s\n", deviceName);
		return SBG_NULL_POINTER;
	}
}