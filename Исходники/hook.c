//------------------------------------------------------------------------------------
NTSTATUS HookApi()
{
	SMFile posFile ;
	LARGE_INTEGER u64FileSize ;
	LARGE_INTEGER u64CurrentOffset;
	char strImageName[260];
	ANSI_STRING TempImageName ;
	g_uPidList = 0 ;
	if ( !NT_SUCCESS(UnProtectSSDT(&MappedSystemCallTable) ) )
	{
		return STATUS_UNSUCCESSFUL;
	}
	if ( !NT_SUCCESS (SMCreateFileForRead ( &posFile , L"\\??\\C:\\Warm.txt")) ) 
	{
		return STATUS_UNSUCCESSFUL;
	}
	if ( !NT_SUCCESS (SMGetFileLength ( &posFile , &u64FileSize )) ) 
	{
		SMCloseFile(&posFile);
		return STATUS_UNSUCCESSFUL;
	}
	
	if ( !NT_SUCCESS(SMReadFile( &posFile , strImageName , &u64FileSize.LowPart )))
	{
		SMCloseFile(&posFile);
		return STATUS_UNSUCCESSFUL;
	}

	SMCloseFile(&posFile);
	strImageName[min(u64FileSize.LowPart,sizeof (strImageName)-1)] = '\0';
	RtlInitAnsiString (&TempImageName,strImageName);

	if ( !NT_SUCCESS(RtlAnsiStringToUnicodeString (&g_uniImageName,&TempImageName,TRUE)))
	{
		return STATUS_UNSUCCESSFUL;
	}

	PsSetLoadImageNotifyRoutine ( LoadImageNotify );
	PsSetCreateProcessNotifyRoutine(CreateProcessNotify , FALSE);

	oldZwCreateKey = (ZWCREATEKEY)(SYSTEMSERVICE(ZwCreateKey));
	HOOK_SYSCALL (ZwCreateKey , newZwCreateKey ,oldZwCreateKey );

	oldZwDeleteKey = (ZWDELETEKEY)(SYSTEMSERVICE(ZwDeleteKey));
	HOOK_SYSCALL (ZwDeleteKey , newZwDeleteKey  ,oldZwDeleteKey );

	oldZwEnumerateKey = (ZWENUMERATEKEY)(SYSTEMSERVICE(ZwEnumerateKey));
	HOOK_SYSCALL (ZwEnumerateKey , newZwEnumerateKey  ,oldZwEnumerateKey );

    oldZwEnumerateValueKey = (ZWENUMERATEVALUEKEY)(SYSTEMSERVICE(ZwEnumerateValueKey));
	HOOK_SYSCALL (ZwEnumerateValueKey , newZwEnumerateValueKey  ,oldZwEnumerateValueKey );

	oldZwOpenKey = (ZWOPENKEY)(SYSTEMSERVICE(ZwOpenKey));
	HOOK_SYSCALL (ZwOpenKey , newZwOpenKey  ,oldZwOpenKey);

	oldZwQueryValueKey = (ZWQUERYVALUEKEY)(SYSTEMSERVICE(ZwQueryValueKey));
	HOOK_SYSCALL (ZwQueryValueKey , newZwQueryValueKey ,oldZwQueryValueKey);

	oldZwSetValueKey = (ZWSETVALUEKEY)(SYSTEMSERVICE(ZwSetValueKey));
	HOOK_SYSCALL (ZwSetValueKey , newZwSetValueKey ,oldZwSetValueKey);

	oldZwNotifyChangeKey = (ZWNOTIFYCHANGEKEY)(SYSTEMSERVICE(ZwNotifyChangeKey));
	HOOK_SYSCALL (ZwNotifyChangeKey , newZwNotifyChangeKey ,oldZwNotifyChangeKey);

	oldZwLoadDriver = (ZWLOADDRIVER)(SYSTEMSERVICE(ZwLoadDriver));
	HOOK_SYSCALL (ZwLoadDriver , newZwLoadDriver ,oldZwLoadDriver);

	oldZwUnloadDriver = (ZWUNLOADDRIVER)(SYSTEMSERVICE(ZwUnloadDriver));
	HOOK_SYSCALL (ZwUnloadDriver , newZwUnloadDriver ,oldZwUnloadDriver);

	oldZwOpenProcess = (ZWOPENPROCESS)(SYSTEMSERVICE(ZwOpenProcess));
	HOOK_SYSCALL (ZwOpenProcess , newZwOpenProcess,oldZwOpenProcess);

	oldZwOpenSection = (ZWOPENSECTION)(SYSTEMSERVICE(ZwOpenSection));
	HOOK_SYSCALL (ZwOpenSection , newZwOpenSection,oldZwOpenSection);

	oldZwMapViewOfSection = (ZWMAPVIEWOFSECTION)(SYSTEMSERVICE(ZwMapViewOfSection));
	HOOK_SYSCALL (ZwMapViewOfSection , newZwMapViewOfSection, oldZwMapViewOfSection);
	
	oldZwCreateSection = (ZWCREATESECTION)(SYSTEMSERVICE(ZwCreateSection));
	HOOK_SYSCALL (ZwCreateSection , newZwCreateSection, oldZwCreateSection);

	oldZwCreateFile = (ZWCREATEFILE)(SYSTEMSERVICE(ZwCreateFile));
	HOOK_SYSCALL (ZwCreateFile , newZwCreateFile, oldZwCreateFile);

	oldZwDeleteFile = (ZWDELETEFILE)(SYSTEMSERVICE(ZwDeleteFile));
	HOOK_SYSCALL (ZwDeleteFile , newZwDeleteFile, oldZwDeleteFile);

	oldZwOpenFile = (ZWOPENFILE)(SYSTEMSERVICE(ZwOpenFile));
	HOOK_SYSCALL (ZwOpenFile , newZwOpenFile, oldZwOpenFile);

	oldZwQueryVolumeInformationFile = (ZWQUERYVOLUMEINFORMATIONFILE)(SYSTEMSERVICE(ZwQueryVolumeInformationFile));
	HOOK_SYSCALL (ZwQueryVolumeInformationFile , newZwQueryVolumeInformationFile, oldZwQueryVolumeInformationFile);

	oldZwSetVolumeInformationFile = (ZWSETVOLUMEINFORMATIONFILE)(SYSTEMSERVICE(ZwSetVolumeInformationFile));
	HOOK_SYSCALL (ZwSetVolumeInformationFile , newZwSetVolumeInformationFile, oldZwSetVolumeInformationFile);

	oldZwQueryDirectoryFile = (ZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile));
	HOOK_SYSCALL (ZwQueryDirectoryFile , newZwQueryDirectoryFile, oldZwQueryDirectoryFile);

	oldZwFsControlFile = (ZWFSCONTROLFILE)(SYSTEMSERVICE(ZwFsControlFile));
	HOOK_SYSCALL (ZwFsControlFile , newZwFsControlFile, oldZwFsControlFile);

	oldZwDeviceIoControlFile = (ZWDEVICEIOCONTROLFILE)(SYSTEMSERVICE(ZwDeviceIoControlFile));
	HOOK_SYSCALL (ZwDeviceIoControlFile , newZwDeviceIoControlFile,  oldZwDeviceIoControlFile);


	oldZwReadFile = (ZWREADFILE)(SYSTEMSERVICE(ZwReadFile));
	HOOK_SYSCALL (ZwReadFile , newZwReadFile,  oldZwReadFile);


	return STATUS_SUCCESS;

}