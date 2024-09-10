ULONG
BtrInitializeStack(
	__in PBTR_PROFILE_OBJECT Object
	)
{
	ULONG Status;
	ULONG Number;
	ULONG Size;

	//
	// Initialize stack record queue and its lookaside
	//

	InitializeSListHead(&BtrStackRecordQueue);
	InitializeSListHead(&BtrStackRecordLookaside);

	//
	// Initialize stack page list
	//

	BtrInitLock(&BtrStackPageLock);
	InitializeListHead(&BtrStackPageRetireList);

	BtrStackPageFree = BtrAllocateStackPage();
	if (!BtrStackPageFree) {
		return S_FALSE;
	}

	//
	// Initialize stack entry table
	//

	for(Number = 0; Number < STACK_RECORD_BUCKET; Number += 1) {
		BtrInitSpinLock(&BtrStackTable.Hash[Number].SpinLock, 100);
		InitializeListHead(&BtrStackTable.Hash[Number].ListHead);
	}

	BtrStackTable.Count = 0;

	//
	// Initialize mapping object for stack record file
	//

	Size = GetFileSize(Object->StackFileObject, NULL);
	if (Size < STACK_FILE_INCREMENT) {

		Status = BtrExtendFileLength(Object->StackFileObject, STACK_FILE_INCREMENT);
		if (Status != S_OK) {
			return Status;
		}

		SetFilePointer(Object->StackFileObject, 0, NULL, FILE_BEGIN);
		BtrSharedData->StackFileLength = STACK_FILE_INCREMENT;
	}
	
	BtrSharedData->StackValidLength = 0;

	RtlZeroMemory(&BtrStackMapping, sizeof(BTR_MAPPING_OBJECT));
	BtrStackMapping.Object = CreateFileMapping(Object->StackFileObject, NULL, 
		                                       PAGE_READWRITE, 0, 0, NULL);
	if (!BtrStackMapping.Object) {
		return GetLastError();
	}

	BtrStackMapping.FileLength = BtrSharedData->StackFileLength;
	return S_OK;
}