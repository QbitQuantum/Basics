HANDLE ControlUnit::OpenComPort(const char *name)
{
	HANDLE handle = ::CreateFileA(name, GENERIC_READ|GENERIC_WRITE, 0/*exclusive access*/, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (handle != INVALID_HANDLE_VALUE) {
		SetupComm(handle, 2048, 2048);

		COMMTIMEOUTS com_time_outs;
		com_time_outs.ReadIntervalTimeout = 0xFFFFFFFF;
		com_time_outs.ReadTotalTimeoutMultiplier = 0;
		com_time_outs.ReadTotalTimeoutConstant = 1000;
		com_time_outs.WriteTotalTimeoutMultiplier = 0;
		com_time_outs.WriteTotalTimeoutConstant = 1000;
		if(!SetCommTimeouts(handle, &com_time_outs)) {
			::CloseHandle(handle);
			return INVALID_HANDLE_VALUE;
		}
		DCB com_param;
		memset(&com_param, 0x00, sizeof(com_param));
		if (!GetCommState(handle, &com_param)) {
			::CloseHandle(handle);
			return INVALID_HANDLE_VALUE;
		}
		com_param.BaudRate = CBR_9600;
		com_param.ByteSize = 8;
		com_param.StopBits = ONESTOPBIT;
		com_param.Parity = NOPARITY;
		com_param.fAbortOnError = TRUE;
		com_param.fDtrControl = DTR_CONTROL_DISABLE;
		com_param.fRtsControl = RTS_CONTROL_DISABLE;
		com_param.fInX = FALSE;
		com_param.fOutX = FALSE;
		com_param.XonLim = 128;
		com_param.XoffLim = 128;
		com_param.fNull = FALSE;
		if (!SetCommState(handle, &com_param)) {
			::CloseHandle(handle);
			return INVALID_HANDLE_VALUE;
		}
		::PurgeComm(handle, PURGE_RXCLEAR|PURGE_TXABORT);
		::CancelIo(handle);
		::Sleep(2000); // Без этого не работает. Скорее всего что ардуина не увспевает сконфигурироваться.
		return handle;
	}
	return INVALID_HANDLE_VALUE;
}