DWORD
SerialWrapper::Read(CString& data)
{
	DWORD dwBytesTransferred;
	DWORD dwCommModemStatus; 

	WaitCommEvent(_hport, &dwCommModemStatus, 0); //wait for character
	if (dwCommModemStatus & EV_RXCHAR)
		ReadFile(_hport, _readBuffer, BUFF_SIZE, &dwBytesTransferred, 0);
	else if (dwCommModemStatus & EV_ERR)
		return 0;//Error;
	CString ret((LPCSTR)&_readBuffer, dwBytesTransferred);
	data.Append(ret);
	return dwBytesTransferred;
}