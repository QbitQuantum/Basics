int NiashLibUsbOpen(char const * const pszName, EScannerModel* const peModel)
{
	//Open a handle to the device (FILE_FLAG_OVERLAPPED for WinUSB)
	
	s_hDevice = CreateFileA(pszName, GENERIC_READ|GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, NULL);
	if(s_hDevice == INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"CreateFile: %s\n", _com_error(GetLastError()).ErrorMessage());
		return -1;
	}

	DEVICE_DESCRIPTOR dd;
	DWORD dwBytesReturned;
	if(!DeviceIoControl(s_hDevice,static_cast<DWORD>(IOCTL_GET_DEVICE_DESCRIPTOR),nullptr,0,&dd,sizeof(dd),&dwBytesReturned,nullptr))
	{
		wprintf_s(L"DeviceIoControl: %s\n", _com_error(GetLastError()).ErrorMessage());
		return -1;
	}

	//Report device to niash
	TScannerModel* pModel;
	MatchUsbDevice(dd.usVendorId,dd.usProductId,&pModel);
	*peModel = pModel->eModel;

	return 1;
}