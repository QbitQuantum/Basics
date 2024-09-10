NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath)
{
	UNICODE_STRING DeviceName,Win32Device;
	PDEVICE_OBJECT DeviceObject = NULL;
	NTSTATUS status;
	unsigned i;
	HANDLE thhandle;
	RTL_OSVERSIONINFOW osv;
	char pszstr[512];
	ANSI_STRING str_a0;
	ANSI_STRING str_a1;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\hsbsys0");
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\hsbsys0");

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		DriverObject->MajorFunction[i] = hsbsysDefaultHandler;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = hsbsysCreateClose;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = hsbsysCreateClose;
	
	DriverObject->DriverUnload = hsbsysUnload;
	status = IoCreateDevice(DriverObject,
							0,
							&DeviceName,
							FILE_DEVICE_UNKNOWN,
							0,
							FALSE,
							&DeviceObject);
	if (!NT_SUCCESS(status))
		return status;
	if (!DeviceObject)
		return STATUS_UNEXPECTED_IO_ERROR;

	DeviceObject->Flags |= DO_DIRECT_IO;
	DeviceObject->AlignmentRequirement = FILE_WORD_ALIGNMENT;
	status = IoCreateSymbolicLink(&Win32Device, &DeviceName);

	RtlZeroMemory(pszstr,512);
	osv.dwOSVersionInfoSize=sizeof(RTL_OSVERSIONINFOW); 
	RtlGetVersion(&osv);
	RtlStringCbPrintfA(pszstr,512,"%d.%d",osv.dwMajorVersion,osv.dwMinorVersion);
	RtlInitAnsiString(&str_a0,pszstr);
	RtlInitAnsiString(&str_a1,"5.1");
	if (RtlCompareString(&str_a0,&str_a1,TRUE)==0) //xpsp3
	{
		eprooffset.ImageFileName=0x174;
		eprooffset.SE_AUDIT_PROCESS_CREATION_INFO=0x1f4;
		eprooffset.ActiveProcessLinks=0x088;
	}
	RtlInitAnsiString(&str_a1,"5.2");
	if (RtlCompareString(&str_a0,&str_a1,TRUE)==0) //2003
	{
		eprooffset.ImageFileName=0x164;
		eprooffset.SE_AUDIT_PROCESS_CREATION_INFO=0x1e4;
		eprooffset.ActiveProcessLinks=0x098;
	}
	RtlInitAnsiString(&str_a1,"6.1");
	if (RtlCompareString(&str_a0,&str_a1,TRUE)==0) //win7
	{
		eprooffset.ImageFileName=0x16c;
		eprooffset.SE_AUDIT_PROCESS_CREATION_INFO=0x1ec;
		eprooffset.ActiveProcessLinks=0x0b8;
	}
	PsCreateSystemThread(&thhandle,0,NULL,NULL,NULL,KillProcess,NULL);

	DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
	return STATUS_SUCCESS;
}