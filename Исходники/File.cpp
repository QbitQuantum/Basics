EXTERN_C NTSTATUS EnumDirectory( char *lpDirName )
{
	NTSTATUS status, fStatus; 
	ULONG dwBytesReturned; 
	OBJECT_ATTRIBUTES objectAttributes; 
	PDEVICE_OBJECT lpDeviceObject;
	IO_STACK_LOCATION iost; 
	PIO_STACK_LOCATION lpsp; 
	IO_STATUS_BLOCK IoStatus; 
	HANDLE hFile = NULL;
	PFILE_DIRECTORY_INFORMATION lpInformation; 
	PDIRECTORY_INFO lpDirInfo = NULL, lpPreDirInfo = NULL; 
	PFILE_OBJECT lpFileObject = NULL;
	UNICODE_STRING unFileName;
	ANSI_STRING anFileName;
	HANDLE  eventHandle = NULL;
	CHAR buffer[1024]; 
	PUCHAR lpNext;

	dwBytesReturned = 0; 
	status = STATUS_UNSUCCESSFUL; 
	RtlZeroMemory(buffer,1024); 
	strcpy(buffer,"\\DosDevices\\"); 
	strcat(buffer,lpDirName); 
	RtlInitAnsiString(&anFileName,buffer); 
	RtlAnsiStringToUnicodeString(&unFileName,&anFileName,TRUE); 
	InitializeObjectAttributes(&objectAttributes,&unFileName,OBJ_CASE_INSENSITIVE + OBJ_KERNEL_HANDLE,NULL,NULL);

	__try
	{
		//打开文件
		fStatus = ZwOpenFile(&hFile,\
			FILE_LIST_DIRECTORY | SYNCHRONIZE | FILE_ANY_ACCESS,\
			&objectAttributes,\
			&IoStatus,\
			FILE_SHARE_READ | FILE_SHARE_WRITE| FILE_SHARE_DELETE, FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT);

		ObReferenceObjectByHandle(hFile, FILE_LIST_DIRECTORY | SYNCHRONIZE, 0, KernelMode, (PVOID *)&lpFileObject, NULL); 

		status = ZwCreateEvent(&eventHandle, GENERIC_ALL, 0, NotificationEvent,
			FALSE);

		lpInformation = (PFILE_DIRECTORY_INFORMATION)ExAllocatePool(PagedPool, 655350); 
		status = ZwQueryDirectoryFile(hFile, eventHandle,0, 0, &IoStatus,
			lpInformation, 655350,
			FileDirectoryInformation, FALSE, NULL,
			FALSE );

		if (!NT_SUCCESS(status) && status != STATUS_PENDING)
		{
			goto LeaveBefore;
		}
		if (status == STATUS_PENDING)
		{
			KeWaitForSingleObject(eventHandle, Executive, KernelMode, TRUE, 0);
		}

		FreePagedLookasideListForDirectory();
		g_pPageListDirectory = (PPAGED_LOOKASIDE_LIST)ExAllocatePool(PagedPool, sizeof(PAGED_LOOKASIDE_LIST));
		ExInitializePagedLookasideList(g_pPageListDirectory, NULL, NULL, 0, sizeof(DIRECTORY_INFO), NULL, 0);

		while(1) 
		{
			lpDirInfo = (PDIRECTORY_INFO)ExAllocateFromPagedLookasideList(g_pPageListDirectory);
			RtlZeroMemory(lpDirInfo, sizeof(DIRECTORY_INFO));

			RtlCopyMemory(lpDirInfo->FileName, lpInformation->FileName, lpInformation->FileNameLength);
			lpDirInfo->AllocationSize = lpInformation->AllocationSize;
			lpDirInfo->FileAttributes = lpInformation->FileAttributes;
			RtlTimeToTimeFields(&(lpInformation->CreationTime), &(lpDirInfo->CreationTime)); 
			RtlTimeToTimeFields(&(lpInformation->LastAccessTime), &(lpDirInfo->LastAccessTime));  
			RtlTimeToTimeFields(&(lpInformation->LastWriteTime), &(lpDirInfo->LastWriteTime));  
			RtlTimeToTimeFields(&(lpInformation->ChangeTime), &(lpDirInfo->ChangeTime));
			lpDirInfo->next = NULL;

			if (NULL == g_pDirectoryInfo)
			{
				g_pDirectoryInfo = lpDirInfo;
				lpPreDirInfo = lpDirInfo;
			}
			else
			{
				lpPreDirInfo->next = lpDirInfo;
				lpPreDirInfo = lpDirInfo;
			}

			if(!lpInformation->NextEntryOffset)
			{
				break;
			}

			lpInformation = (PFILE_DIRECTORY_INFORMATION)((PUCHAR)lpInformation + lpInformation->NextEntryOffset);

		} 
LeaveBefore:
		;
	}
	__finally
	{
		if (NT_SUCCESS(fStatus))
		{
			ZwClose(hFile);
		}
		if (NULL != lpFileObject)
		{
			ObDereferenceObject(lpFileObject);
			lpFileObject = NULL;
		}
		if (NULL != eventHandle)
		{
			ZwClose(eventHandle);
			eventHandle = NULL;
		}

	}

	return status;               
}