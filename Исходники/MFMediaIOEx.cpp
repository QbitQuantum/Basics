MFMediaIOEx::ReadResult MFMediaIOEx::GetReadResult()
{
	HANDLE handles[] = {_hEventRead,_hEventCancel};
	DWORD result = WaitForMultipleObjectsEx(_countof(handles),handles,FALSE,_dwReadTimeout,FALSE);
	if (result == WAIT_TIMEOUT)
		return ReadTimeout;
	else if (result == WAIT_FAILED)
		return ReadFailed;
	return result == 0 ? ReadOK:ReadCancel;
}