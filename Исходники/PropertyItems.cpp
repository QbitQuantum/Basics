// Convert double to CString
CString FloatToString(double x)
{
	char strbuf[32];
	_gcvt(x, 7, strbuf);
	
	// Last character is a dot - remove it
	int lastch = strlen(strbuf) - 1;
	if (strbuf[lastch] == '.')
		strbuf[lastch] = '\0';

	return strbuf;
}