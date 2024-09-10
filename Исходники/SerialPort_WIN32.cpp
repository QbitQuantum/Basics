int SerialPortImpl::pollImpl(char* buffer, std::size_t size, const Poco::Timespan& timeout)
{
	COMMTIMEOUTS prevCTO;
	if (!GetCommTimeouts(_handle, &prevCTO))
	{
		throw Poco::IOException("error getting serial port timeouts");
	}

	COMMTIMEOUTS cto;
	cto.ReadIntervalTimeout         = CHARACTER_TIMEOUT;
	cto.ReadTotalTimeoutConstant    = static_cast<DWORD>(timeout.totalMilliseconds());
	cto.ReadTotalTimeoutMultiplier  = 0;
	cto.WriteTotalTimeoutConstant   = MAXDWORD;
	cto.WriteTotalTimeoutMultiplier = 0;
	if (!SetCommTimeouts(_handle, &cto))
	{
		throw Poco::IOException("error setting serial port timeouts on serial port");
	}

	try
	{
		DWORD bytesRead = 0;
		if (!ReadFile(_handle, buffer, size, &bytesRead, NULL))
		{
			throw Poco::IOException("failed to read from serial port");
		}
		SetCommTimeouts(_handle, &prevCTO);
		return (bytesRead == 0) ? -1 : bytesRead;
	}
	catch (...)
	{
		SetCommTimeouts(_handle, &prevCTO);
		throw;
	}
}