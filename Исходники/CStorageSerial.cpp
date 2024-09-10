/*--------------------------------------------------------------------------------*/
BOOL	CStorageSerial::QuerySystemStorage(LPTSTR Volume,PULONG DeviceNumber)
{
	BOOL	Result = FALSE;
	HANDLE	FileHandle = INVALID_HANDLE_VALUE;
	ULONG	NumberOfReturnBytes = 0;
	TCHAR	DeviceName[64] = {0};
	STORAGE_DEVICE_NUMBER	StorageDeviceNumber = {0};

	if(IsUserAnAdmin())
	{
		_stprintf_s(DeviceName,sizeof(DeviceName)/sizeof(TCHAR),_T("\\\\.\\%s"),Volume);
		FileHandle = CreateFile(DeviceName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,NULL);
		if(FileHandle != INVALID_HANDLE_VALUE)
		{
			Result = DeviceIoControl(FileHandle,
				IOCTL_STORAGE_GET_DEVICE_NUMBER,
				NULL,
				0,
				&StorageDeviceNumber,
				sizeof(StorageDeviceNumber),
				&NumberOfReturnBytes,
				NULL);
			if(Result)
			{
				*DeviceNumber = StorageDeviceNumber.DeviceNumber;
			}
			CloseHandle(FileHandle);
		}
	}
	return	(Result);
}