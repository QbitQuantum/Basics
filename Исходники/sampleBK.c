VOID
	MyThreadStart(__in PVOID  StartContext){
		HANDLE   handle;//Create File handle
		NTSTATUS ntstatus;
		NTSTATUS timerStatus;
		//IO_STATUS_BLOCK    ioStatusBlock;
		//OBJECT_ATTRIBUTES ObjAttr;
		//UNICODE_STRING path;
		LARGE_INTEGER timeout;
//#define  BUFFER_SIZE 30
	//	CHAR     buffer[BUFFER_SIZE];
		//size_t  cb;

		NTSTATUS Status;
		HANDLE hEvent;
		//OBJECT_ATTRIBUTES oa;
		//UNICODE_STRING us;
		int counter=20;
		SIZE_T BytesNUM;
		char* dataPtr;

		__debugbreak();
		dataPtr="123";
		BytesNUM=strlen(dataPtr)*sizeof(char);
		WriteToRingBuffer(&dataPtr, BytesNUM);
		FlushRingBuffre();
		RtlInitUnicodeString(
			&path,
			L"\\DosDevices\\C:\\MyLogger.txt");
		InitializeObjectAttributes(
			&ObjAttr,
			&path,  			//ObjectName
			OBJ_CASE_INSENSITIVE, 	//Attributes
			NULL,			//RootDirectory
			NULL);			//SecurityDescriptor
		// Do not try to perform any file operations at higher IRQL levels.
		// Instead, you may use a work item or a system worker thread to perform file operations.

		if(KeGetCurrentIrql() != PASSIVE_LEVEL)
			//  return STATUS_INVALID_DEVICE_STATE; 
			DbgPrint("STATUS_INVALID_DEVICE_STATE\n");

		ntstatus = ZwCreateFile(&handle,
			GENERIC_WRITE,
			&ObjAttr, &ioStatusBlock, NULL,
			FILE_ATTRIBUTE_NORMAL,
			0,
			FILE_OVERWRITE_IF, 
			FILE_SYNCHRONOUS_IO_NONALERT,
			NULL, 0);


		timeout.QuadPart = -5 * 1000000;

		RtlInitUnicodeString(
			&us,
			L"\\BaseNamedObjects\\TestEvent");

		InitializeObjectAttributes(
			&oa,
			&us,  			//ObjectName
			OBJ_CASE_INSENSITIVE, 	//Attributes
			NULL,			//RootDirectory
			NULL);			//SecurityDescriptor

		Status = ZwCreateEvent(&hEvent,
			EVENT_ALL_ACCESS,
			&oa,
			NotificationEvent,
			FALSE);

		if(NT_SUCCESS(Status)){
			DbgPrint("Event created");
		} else {
			DbgPrint("Event Not created");
		}

		Status = ObReferenceObjectByHandle(
			hEvent, 		//Handle
			EVENT_ALL_ACCESS,	//DesiredAccess
			NULL,			//ObjectType
			KernelMode,		//AccessMode
			&pEvent,		//Object
			NULL);			//HandleInformation

		if (!NT_SUCCESS(Status)) {
			ZwClose(hEvent);
			DbgPrint("Failed to reference event \n");
			//return Status;
		};

		while(counter!=0){



			timerStatus = KeWaitForSingleObject(
				pEvent,
				Executive,
				KernelMode,
				FALSE,
				&timeout
				);




			if(timerStatus == STATUS_TIMEOUT){
				if(NT_SUCCESS(ntstatus)) {
					ntstatus = RtlStringCbPrintfA(buffer, sizeof(buffer), "This is %d test\r\n", counter);
					if(NT_SUCCESS(ntstatus)) {
						ntstatus = RtlStringCbLengthA(buffer, sizeof(buffer), &cb);
						if(NT_SUCCESS(ntstatus)) {
							ntstatus = ZwWriteFile(handle, NULL, NULL, NULL, &ioStatusBlock,
								buffer, cb, NULL, NULL);
						}
					}
					//ZwClose(handle);
				}
			}
			counter--;
		}
		ZwClose(handle);
}