void CCommandLine::SetParm(const char *pszParm, int iValue)
{
	char pszValue[64];
	_snprintf(pszValue, sizeof(pszValue), "%d", iValue);
	SetParm(pszParm, iValue);
}