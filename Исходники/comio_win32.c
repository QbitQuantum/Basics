int comGetModemStatus(COM_HANDLE handle)
{
	DWORD status=0;
	
	if(GetCommModemStatus(handle, &status))
		return status;
	else
		return COM_ERROR;
}