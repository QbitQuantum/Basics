/////////////////////////////////////////////////////
//                                                 //
// CheckDriver()                                   //
//                                                 //
/////////////////////////////////////////////////////
//Description:  Runs hook/detour detection routines
//				on the passed-in driver.
//
//				Note:  pHookTable and pDetourTable are
//				both optional, depending on which test
//				you wish to run.
//
//Returns:      void
/////////////////////////////////////////////////////
NTSTATUS CheckDriver(__in PUNICODE_STRING puDriverName, 
					 __in PUNICODE_STRING puDriverDeviceName, 
					 __inout_opt PHOOKED_DISPATCH_FUNCTIONS_TABLE pHookTable,
					 __inout_opt PDETOURED_DISPATCH_FUNCTIONS_TABLE pDetourTable)
{
	PMODULE_LIST pModuleList;
	ULONG bufsize=0;
	PULONG returnLength=0;
	ULONG modsize=0,modbase=0;
	CHAR ModuleName[256];
	WCHAR wModuleName[256];
	UNICODE_STRING uModuleName;
	ANSI_STRING aModuleName;
	PCHAR nameStart;
	NTSTATUS nt;
	int i;

	//0 buffer size is returned on failure
	bufsize=GetInformationClassSize(SystemModuleInformation);
	if (bufsize == 0)
		return STATUS_UNSUCCESSFUL;

	//loop through list of loaded drivers
	pModuleList=ExAllocatePoolWithTag(NonPagedPool,bufsize,CW_TAG);

	//oops, out of memory...
	if (pModuleList == NULL)
	{
		DbgPrint("CheckDriver():  Out of memory.\n");
		return STATUS_UNSUCCESSFUL;
	}

	nt=ZwQuerySystemInformation(SystemModuleInformation,pModuleList,bufsize,returnLength);

	if (nt != STATUS_SUCCESS)
	{
		DbgPrint("CheckDriver():  ZwQuerySystemInformation() failed.\n");
		if (pModuleList != NULL)
			ExFreePoolWithTag(pModuleList,CW_TAG);
		return STATUS_UNSUCCESSFUL;
	}

	//loop through the module list looking for the driver we are interested in;
	//retrieve it's load address and size.
	for(i=0;i<(long)pModuleList->ModuleCount;i++)
	{
		nameStart=pModuleList->Modules[i].ImageName+pModuleList->Modules[i].ModuleNameOffset;
		memcpy(ModuleName,nameStart,256-pModuleList->Modules[i].ModuleNameOffset);
		//since ZwQuerySystemInformation() returns a CHAR[256] and we need to compare it to a UNICODE_STRING, convert...
		RtlInitAnsiString(&aModuleName,ModuleName);
		RtlAnsiStringToUnicodeString(&uModuleName,&aModuleName,TRUE);

		//if we are on the driver we care about
		if (RtlCompareUnicodeString(&uModuleName,puDriverName,TRUE) == 0)
		{
			modsize=(ULONG)pModuleList->Modules[i].Size;
			modbase=(ULONG)pModuleList->Modules[i].Base;
			//free the tmp unicode string
			if (uModuleName.Buffer != NULL)
				RtlFreeUnicodeString(&uModuleName);
			break;
		}

		//free the tmp unicode string
		if (uModuleName.Buffer != NULL)
			RtlFreeUnicodeString(&uModuleName);
	}

	//bail if we didnt find the driver we were asked to look for.
	if (modsize == 0 || modbase == 0)
	{
		ExFreePoolWithTag(pModuleList,CW_TAG);
		DbgPrint("CheckDriver():  Failed to get this driver's size and base - maybe it's not loaded?\n");
		return STATUS_UNSUCCESSFUL;
	}

	DbgPrint("CheckDriver():  Found driver %wZ loaded at base address 0x%08x",puDriverName,modbase);

	//convert the driver device name to a PCWSTR
	//mbstowcs(uDriverDeviceName,driverDeviceName,256);

	//go ahead and save the driver name and device name in both tables
	if (pHookTable != NULL)
	{
		RtlInitUnicodeString(&pHookTable->DriverName,puDriverName->Buffer);
		RtlInitUnicodeString(&pHookTable->DriverDeviceName,puDriverDeviceName->Buffer);
	}
	if (pDetourTable != NULL)
	{
		//initialize the max length of the dest string
		RtlInitUnicodeString(&pDetourTable->DriverName,puDriverName->Buffer);
		RtlInitUnicodeString(&pDetourTable->DriverDeviceName,puDriverDeviceName->Buffer);
	}

	//----------------
	// ** IRP HOOKS **
	//----------------
	if (!GetIrpTableHooksAndDetours(puDriverName,puDriverDeviceName,modbase,modsize, pHookTable, pDetourTable))
	{
		ExFreePoolWithTag(pModuleList,CW_TAG);
		return STATUS_UNSUCCESSFUL;
	}

	if (pModuleList != NULL)
		ExFreePoolWithTag(pModuleList,CW_TAG);

	return STATUS_SUCCESS;
}