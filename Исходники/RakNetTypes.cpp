const char *SystemAddress::ToString(bool writePort) const
{
	if (*this==UNASSIGNED_SYSTEM_ADDRESS)
		return "UNASSIGNED_SYSTEM_ADDRESS";

#ifdef _XBOX360
	return "";
#else
	static unsigned char strIndex=0;
	static char str[8][22];
	in_addr in;
	in.s_addr = binaryAddress;
	strcpy(str[strIndex], inet_ntoa( in ));
	if (writePort)
	{
		strcat(str[strIndex], ":");
		Itoa(port, str[strIndex]+strlen(str[strIndex]), 10);
	}

	unsigned char lastStrIndex=strIndex;
	strIndex++;
	if (strIndex==8)
		strIndex=0;
	
	return (char*) str[lastStrIndex];
#endif
}