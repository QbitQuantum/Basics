extern "C" __declspec (dllexport) bool SerialGate::GetLine(IN_LINES_NAME ln)
{
	if(!state)
		return 0;

	unsigned long ul = 0;

	GetCommModemStatus(m_hFile, &ul);
		
	if(ul == 0x10 && ln == CTS)
	{
		return true;
	}

	if(ul == 0x20 && ln == DSR)
	{
		return true;	
	}

	if(ul == 0x40 && ln == RING)
	{
		return true;
	}

	if(ul == 0x80 && ln == RLSD)
	{
		return true;
	}		

	return false;
}