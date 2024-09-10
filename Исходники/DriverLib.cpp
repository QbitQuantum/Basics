	int ReadPage(ULONG64 StartAddress, unsigned char buffer[])
	{
		HANDLE hDevice;
		ULONG bytesReturned;
		LARGE_INTEGER largeStart;

		hDevice = CreateFileA("\\\\.\\pmem", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hDevice == INVALID_HANDLE_VALUE)
			return 1;
		largeStart.QuadPart = StartAddress;
		if (0xFFFFFFFF == SetFilePointerEx(hDevice, largeStart, NULL, FILE_BEGIN))
		{
			CloseHandle(hDevice);
			return 3;
		}
		if (!ReadFile(hDevice, buffer, 4096, &bytesReturned, NULL))
		{
			CloseHandle(hDevice);
			return 4;
		}
		CloseHandle(hDevice);
		return 0;
	}