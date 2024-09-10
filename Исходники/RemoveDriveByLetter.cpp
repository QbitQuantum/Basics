int removeDrive(char drive)
{
	char driveLetter = drive;
    driveLetter &= ~0x20;

	if ( driveLetter < 'A' || driveLetter > 'Z' ) {
		return 1;
	}

	wchar_t szRootPath[] = L"X:\\";   // "X:\"  -> for GetDriveType
	szRootPath[0] = driveLetter;

	wchar_t szDevicePath[] = L"X:";   // "X:"   -> for QueryDosDevice
	szDevicePath[0] = driveLetter;

	wchar_t szVolumeAccessPath[] = L"\\\\.\\X:";   // "\\.\X:"  -> to open the volume
	szVolumeAccessPath[4] = driveLetter;

	long DeviceNumber = -1;

	HANDLE hVolume = CreateFile(szVolumeAccessPath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hVolume == INVALID_HANDLE_VALUE) {
		return 1;
	}

	STORAGE_DEVICE_NUMBER sdn;
	DWORD dwBytesReturned = 0;
	long res = DeviceIoControl(hVolume, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0, &sdn, sizeof(sdn), &dwBytesReturned, NULL);
	if ( res ) {
		DeviceNumber = sdn.DeviceNumber;
	}
	CloseHandle(hVolume);

	if ( DeviceNumber == -1 ) {
		return 1;
	}

	UINT DriveType = GetDriveType(szRootPath);

	char szDosDeviceName[MAX_PATH];
	res = QueryDosDevice(szDevicePath, (LPWSTR)szDosDeviceName, MAX_PATH);
	if ( !res ) {
		return 1;
	}

	DEVINST DevInst = GetDrivesDevInstByDeviceNumber(DeviceNumber, DriveType, szDosDeviceName);

	if ( DevInst == 0 ) {
		return 1;
	}

	PNP_VETO_TYPE VetoType = PNP_VetoTypeUnknown; 
	WCHAR VetoNameW[MAX_PATH];
	VetoNameW[0] = 0;
	bool bSuccess = false;


	DEVINST DevInstParent = 0;
	res = CM_Get_Parent(&DevInstParent, DevInst, 0); 

    for ( long tries=1; tries<=3; tries++ ) {
		VetoNameW[0] = 0;

        res = CM_Request_Device_EjectW(DevInstParent, &VetoType, VetoNameW, MAX_PATH, 0);
        bSuccess = (res==CR_SUCCESS && VetoType==PNP_VetoTypeUnknown);
		if ( bSuccess )  { 
			break;
		}

        Sleep(500);
	}

	if ( bSuccess ) {
		printf("Success\n\n");
		return 0;
	}

	printf("failed\n");
	
	printf("Result=0x%2X\n", res);

	if ( VetoNameW[0] ) {
		printf("VetoName=%ws)\n\n", VetoNameW);
	}	
	return 1;
}