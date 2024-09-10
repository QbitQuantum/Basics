// 读设备
USBHIDDLL_API int __stdcall USBHIDReadByte(USBHANDLE handle, BYTE* byte, int len)
{
    DWORD numberOfByteRead = 0;

    if (handle != INVALID_HANDLE_VALUE)
    {
		CancelIo(handle);

        int Result = ReadFile 
            (handle, 
			byte,
			len,
            &numberOfByteRead,
			&HIDOverlapped);

		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(handle, INFINITE);
			GetOverlappedResult(handle, &HIDOverlapped, &numberOfByteRead, FALSE);
		}
    }
    return numberOfByteRead;
}