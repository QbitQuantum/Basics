void ChinavisionAPI::threadProc() {

	//========================
	OVERLAPPED	overlappedRead;
	HANDLE		events[2];
	DWORD		result;
	UCHAR		buffer[4];
	ULONG		length;
	//========================

	memset(&overlappedRead,0,sizeof(OVERLAPPED));

	overlappedRead.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_exitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	events[0] = overlappedRead.hEvent;
	events[1] = m_exitEvent;

	while(1) {

		memset(buffer,0,sizeof(buffer));	//sometiemes only reads 3 bytes

		WinUsb_ReadPipe(m_usbHandle, m_inPipeId, buffer, sizeof(buffer), &length, &overlappedRead);

		result = WaitForMultipleObjects(2,events,FALSE,INFINITE);

		if(result==WAIT_OBJECT_0) {

			//=============
			DWORD tempCode;
			//=============

			tempCode = *(DWORD*)buffer;
			printf("irCode %x\n",tempCode>>8);

			printf("length %i\n",length);

			for(DWORD i=0; i<length; i++) {
				printf("buffer[%i]",(int)buffer[i]);
			}
			printf("\n");

			tempCode = tempCode >> 8;

			if(tempCode) {
				m_irCode = *(DWORD*)buffer;
				SetEvent(m_dataReadyEvent);
			}
		}
		else {
			break;