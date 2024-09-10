WideString DeviceInfo::GetName()
{
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ms724295(v=vs.85).aspx
	char16 compName[MAX_COMPUTERNAME_LENGTH + 1];
	uint32 length = MAX_COMPUTERNAME_LENGTH + 1;

	bool nameRecieved = GetComputerNameW(compName, (LPDWORD) &length) != FALSE;
	if(nameRecieved)
	{
		return WideString(compName, length);
	}

    return WideString ();
}