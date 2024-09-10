JNIEXPORT jint JNICALL Java_com_fazecast_jSerialComm_SerialPort_waitForEvent(JNIEnv *env, jobject obj, jlong serialPortFD)
{
	HANDLE serialPortHandle = (HANDLE)serialPortFD;
	if (serialPortHandle == INVALID_HANDLE_VALUE)
		return 0;
	OVERLAPPED overlappedStruct = {0};
	overlappedStruct.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (overlappedStruct.hEvent == NULL)
	{
		CloseHandle(overlappedStruct.hEvent);
		return 0;
	}

	// Wait for a serial port event
	DWORD eventMask, numBytesRead, readResult = WAIT_FAILED;
	if (WaitCommEvent(serialPortHandle, &eventMask, &overlappedStruct) == FALSE)
	{
		if (GetLastError() != ERROR_IO_PENDING)			// Problem occurred
		{
			// Problem reading, close port
			PurgeComm(serialPortHandle, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
			while (!CloseHandle(serialPortHandle));
			serialPortHandle = INVALID_HANDLE_VALUE;
			env->SetLongField(obj, serialPortHandleField, -1l);
			env->SetBooleanField(obj, isOpenedField, JNI_FALSE);
		}
		else
		{
			BOOL continueWaiting = TRUE;
			while (continueWaiting)
			{
				readResult = WaitForSingleObject(overlappedStruct.hEvent, 750);
				continueWaiting = ((readResult == WAIT_TIMEOUT) && (env->GetIntField(obj, eventFlagsField) != 0));
			}
			if ((readResult != WAIT_OBJECT_0) || (GetOverlappedResult(serialPortHandle, &overlappedStruct, &numBytesRead, TRUE) == FALSE))
				numBytesRead = 0;
		}
	}

	// Return type of event if successful
	CloseHandle(overlappedStruct.hEvent);
	return ((eventMask & EV_RXCHAR) > 0) ? com_fazecast_jSerialComm_SerialPort_LISTENING_EVENT_DATA_AVAILABLE :
			(((eventMask & EV_TXEMPTY) > 0) ? com_fazecast_jSerialComm_SerialPort_LISTENING_EVENT_DATA_WRITTEN : 0);
}