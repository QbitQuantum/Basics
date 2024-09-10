/*
 * Opens the specified adapter and binds the protocol to it
 *
 * Arguments
 *		AdapterName		- The name of the adapter with which binding should happen
 *
 * Return Value
 *		Return TRUE if successfully bound otherwise returns FALSE
 *
 */
BOOL PKTOpenAdapter (PNDIS_STRING pAdapterName)
{
	POPEN_INSTANCE	pOI;
	NDIS_STATUS		nsOpen;
	NDIS_STATUS		nsError;
	SYSTEMTIME		SystemTime;
	FILETIME		FileTime;
	LARGE_INTEGER	liSysTime;
	LARGE_INTEGER	TimeFreq;
	LARGE_INTEGER	PTime;
	UINT			uiMedium;


	// Check if an instance is already opened
	if (g_pDeviceExtension->pOpenInstance) {
		SetLastError (ERROR_ALREADY_INITIALIZED);
		return FALSE;
	}

	// Time initialization
	GetSystemTime (&SystemTime);
	if (! (SystemTimeToFileTime (&SystemTime, &FileTime) &&
		QueryPerformanceCounter (&PTime) && QueryPerformanceFrequency (&TimeFreq))) {
		return FALSE;
	}
	NdisMoveMemory (&liSysTime, &FileTime, sizeof (LARGE_INTEGER));
	
	
	
	// allocate an instance that describes the adapter
	NdisAllocateMemory (&pOI, sizeof (OPEN_INSTANCE), 0, NDIS_ADDR_M1);
	if (pOI == NULL) {
		return FALSE;
	}
	NdisZeroMemory (pOI, sizeof (OPEN_INSTANCE));

	// init struct variables
	pOI->bpfprogram			= NULL;		//set an accept-all filter
	pOI->bpfprogramlen		= 0;
	pOI->BufSize			= 0;		//set an empty buffer
	pOI->Buffer				= NULL;		//reset the buffer
	pOI->Bhead				= 0;
	pOI->Btail				= 0;
	pOI->BLastByte			= 0;
	pOI->TimeOut			= 0;		//reset the timeouts


	// create the shared name read event
	pOI->ReadEvent = CreateEvent (NULL, FALSE, FALSE, SH_EVENT_NAME);
	if (pOI->ReadEvent == NULL) {
		NdisFreeMemory (pOI, sizeof (OPEN_INSTANCE), 0);
		return FALSE;
	}

	// set time values
	pOI->StartTime.QuadPart = (((liSysTime.QuadPart) % 10000000) * TimeFreq.QuadPart)/10000000;
	liSysTime.QuadPart = liSysTime.QuadPart / 10000000 - 11644473600;
	pOI->StartTime.QuadPart += (liSysTime.QuadPart) * TimeFreq.QuadPart - PTime.QuadPart;


	// allocate pool for the packet headers
	NdisAllocatePacketPool (&nsError, &(pOI->PacketPool), 
		TRANSMIT_PACKETS, sizeof (PACKET_RESERVED));
	if (nsError != NDIS_STATUS_SUCCESS) {
		CloseHandle (pOI->ReadEvent);
		NdisFreeMemory (pOI, sizeof (OPEN_INSTANCE), 0);
		return FALSE;
	}


	// allocate buffer pool for the packet data
	NdisAllocateBufferPool (&nsError, &(pOI->BufferPool), TRANSMIT_PACKETS);
	if (nsError != NDIS_STATUS_SUCCESS) {
		CloseHandle (pOI->ReadEvent);
		NdisFreePacketPool (pOI->PacketPool);
		NdisFreeMemory (pOI, sizeof (OPEN_INSTANCE), 0);
		return FALSE;
	}

	// set status pending
	pOI->Status = NDIS_STATUS_PENDING;

	// open the MAC driver
	NdisOpenAdapter (&nsOpen, &nsError, &pOI->AdapterHandle, &uiMedium, MediumArray,
		NUM_NDIS_MEDIA, g_pDeviceExtension->NdisProtocolHandle, pOI, pAdapterName, 0, NULL);


	if (nsOpen == NDIS_STATUS_PENDING) {
		SuspendExecution (pOI);
	} else {
		PacketOpenAdapterComplete (pOI, nsOpen, nsError);
	}

	// free the packet instance if not successful
	if (pOI->Status != NDIS_STATUS_SUCCESS) {
		CloseHandle (pOI->ReadEvent);
		NdisFreeMemory (pOI, sizeof (OPEN_INSTANCE), 0);
		return FALSE;
	}

	return TRUE;
}