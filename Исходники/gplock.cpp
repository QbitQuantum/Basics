BOOL
VendorSetLock11(
	IN PRAM_DATA_OLD						RamData,
	IN UINT64								SessionId,
	IN PLANSCSI_VENDOR_REQUEST_PDU_HEADER	RequestHeader,
	OUT PLANSCSI_VENDOR_REPLY_PDU_HEADER	ReplyHeader
){
	UINT64					vendorParam;
	UCHAR					lockNo;
	PGENERAL_PURPOSE_LOCK	gpLock;
	LONG					acquired;
	DWORD					dwWaitResult;


	vendorParam = NTOHLL(RequestHeader->VendorParameter);
	lockNo = (UCHAR)((vendorParam>>32) & 0x3);
	gpLock = &RamData->GPLocks[lockNo];

	fprintf(stderr, "VendorSetLock11: Acquiring lock %d.\n", lockNo);

	//
	//	Acquire the mutex for the lock access
	//

	dwWaitResult = WaitForSingleObject(RamData->LockMutex, INFINITE);
	if(dwWaitResult != WAIT_OBJECT_0)
		return FALSE;

	if(gpLock->Acquired == FALSE) {
		//
		//	GP lock acquired
		//
		gpLock->Acquired = TRUE;
		gpLock->Counter ++;
		gpLock->SessionId = SessionId;

		//
		// Set return counter
		//
		
		ReplyHeader->VendorParameter = HTONLL((UINT64)gpLock->Counter);
		
		fprintf(stderr, "VendorSetLock11: lock %d acquired(%ld).\n", lockNo, gpLock->SessionId);

	//
	//	GP lock Already acquired by others
	//

	} else {
		//
		// Set return counter
		//

		ReplyHeader->VendorParameter = HTONLL((UINT64)gpLock->Counter);

		ReleaseMutex(RamData->LockMutex);

		fprintf(stderr, "VendorSetLock11: Lock contention!\n");
		ReplyHeader->Response = LANSCSI_RESPONSE_T_SET_SEMA_FAIL;
		return TRUE;
	}

	ReleaseMutex(RamData->LockMutex);

	return TRUE;
}