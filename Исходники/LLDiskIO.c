// -----------------------------------------------------------------------------------------
PDEVICE_OBJECT
Disk_GetDeviceObjectByLetter(WCHAR DriveLetter)
{
	PDEVICE_OBJECT		pDevice = NULL;
	NTSTATUS			ntStatus;
	
	HANDLE				hDir;
	UNICODE_STRING		us;
	OBJECT_ATTRIBUTES	ObjAttr;
	
	HANDLE				hLink;
	WCHAR				targetNameBuffer[260];
	UNICODE_STRING      targetNameUnicodeString;
	
	PFILE_OBJECT		fileObject;
	IO_STATUS_BLOCK		ioStatus;

	WCHAR				cDrive[3] = L"A:";

	RtlInitUnicodeString(&us, (PWCHAR)L"\\??");
	InitializeObjectAttributes(&ObjAttr, &us, OBJ_CASE_INSENSITIVE, NULL, NULL);
	ntStatus = ZwOpenDirectoryObject(&hDir, DIRECTORY_QUERY,&ObjAttr);
	if(!NT_SUCCESS(ntStatus))
	{
		DbPrint(DC_LLDISKIO, DL_ERROR, ("ZwOpenDirectoryObject %S failed, status %x\n",us.Buffer, ntStatus));
		return NULL;
	}

	cDrive[0] = DriveLetter;
	RtlInitUnicodeString(&us,cDrive);

	InitializeObjectAttributes(&ObjAttr, &us, OBJ_CASE_INSENSITIVE, hDir, NULL);
	ntStatus = ZwOpenSymbolicLinkObject(&hLink, SYMBOLIC_LINK_QUERY, &ObjAttr);
	if(NT_SUCCESS(ntStatus))
	{
		RtlZeroMemory(targetNameBuffer, sizeof(targetNameBuffer));
		targetNameUnicodeString.Buffer = targetNameBuffer;
		targetNameUnicodeString.MaximumLength = sizeof(targetNameBuffer);
		ntStatus = ZwQuerySymbolicLinkObject(hLink, &targetNameUnicodeString, NULL);
		if(NT_SUCCESS(ntStatus))
		{
			if(!wcsncmp(targetNameBuffer,L"\\Device",7))
			{
				HANDLE hFile;
				ntStatus = ZwCreateFile(&hFile, SYNCHRONIZE | FILE_ANY_ACCESS, &ObjAttr, &ioStatus, NULL, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
				if(NT_SUCCESS(ntStatus))
				{
					//!FILE_DEVICE_MASS_STORAGE or FILE_DEVICE_TAPE
					ntStatus = ObReferenceObjectByHandle(hFile, FILE_READ_DATA, NULL, KernelMode, (PVOID*) &fileObject, NULL);
					if(NT_SUCCESS(ntStatus))
					{
						pDevice = fileObject->DeviceObject;
						if (pDevice->Vpb != NULL)
						{
							if (pDevice->Vpb->RealDevice != NULL)
								pDevice = pDevice->Vpb->RealDevice;
						}
						if(pDevice->DeviceType == FILE_DEVICE_DISK || pDevice->DeviceType == FILE_DEVICE_CD_ROM || pDevice->DeviceType == FILE_DEVICE_DVD)
						{
							if(!NT_SUCCESS(ObReferenceObjectByPointer(pDevice, STANDARD_RIGHTS_REQUIRED, *IoDeviceObjectType, KernelMode)))	//dereference will be in caller proc
								pDevice = NULL;
						}
						else
							pDevice = NULL;

						ObDereferenceObject(fileObject);
					}

					ZwClose(hFile);
				}
			}
		}
		ZwClose(hLink);
	}
					
	ZwClose(hDir);

	return pDevice;
}