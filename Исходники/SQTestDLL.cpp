int SerialWrite (char* str)
{
	// The serial port is now ready and we can send/receive data. If
	// the following call blocks, then the other side doesn't support
	// hardware handshaking.
    lLastError = serial.Write(str);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to send data"));

	// if no error
	return 0;
}