void TrimViewString(CmyString &strDst, LPCSTR pszSrc)
{
	int i, nLen;
	BYTE byTmp;
	char szTmp[3];

	strDst.Empty ();
	if (pszSrc == NULL) {
		return;
	}
	nLen = strlen (pszSrc);
	if (nLen <= 0) {
		return;
	}
	ZeroMemory (szTmp, sizeof (szTmp));

	for (i = 0; i < nLen; i ++) {
		byTmp = (BYTE)pszSrc[i];
		if (IsDBCSLeadByte (byTmp)) {
			szTmp[0] = byTmp;
			szTmp[1] = pszSrc[i + 1];
			strDst += szTmp;
			i ++;
			continue;
		}
		if ((byTmp < 0x20) || ((byTmp >= 0x7F) && !((byTmp >= 0xA1) && (byTmp <= 0xDF)))) {
			continue;
		}
		szTmp[0] = byTmp;
		szTmp[1] = 0;
		strDst += szTmp;
	}
}