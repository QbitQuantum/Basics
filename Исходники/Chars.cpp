void CChars::Append(float f, int iNumDecimals)
{
	char	sz[128];
	char	szd[128];

	strcpy(sz, "%.");
	strcat(sz, IToA(iNumDecimals, szd, 10));
	strcat(sz, "f");
	sprintf(szd, sz, f);
	Append(szd);
}