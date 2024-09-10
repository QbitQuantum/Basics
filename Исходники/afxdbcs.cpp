AFX_STATIC BOOL PASCAL _AfxInitDBCS()
{
	CPINFO info;
	GetCPInfo(GetOEMCP(), &info);
	return info.MaxCharSize > 1;
}