int ZipPlatform::MultiByteToWide(const char* szIn, int iInSize, CZipString& szOut, UINT uCodePage)
{	
	szOut.Empty();
	if (iInSize < 0)
	{
		iInSize = (int)std::string(szIn).length();
	}	
	if (iInSize == 0)
	{		
		return 0;
	}
	
	// iLen doesn't include terminating character
	DWORD dwFlags = uCodePage <= CP_OEMCP ? MB_PRECOMPOSED : 0;
	int iLen = MultiByteToWideChar(uCodePage, dwFlags, szIn, iInSize, NULL, 0);
	if (iLen > 0)
	{
		iLen = MultiByteToWideChar(uCodePage, dwFlags, szIn, iInSize, szOut.GetBuffer(iLen), iLen);
		szOut.ReleaseBuffer(iLen);
		ASSERT(iLen > 0);
		if (iLen == 0)
			return -1;
#ifdef _ZIP_UNICODE_NORMALIZE
		// if there is a problem with compilation here, you may need uncomment the block defining WINVER = 0x0600 at the bottom of _features.h file
		if (IsNormalizedString(NormalizationC, szOut, iLen + 1) == TRUE)
			return iLen;		
		int iNewLen = NormalizeString(NormalizationC, szOut, iLen, NULL, 0);
		if (iNewLen <= 0)
		{
			return iLen;
		}
		CZipString szNormalized;
		iNewLen = NormalizeString(NormalizationC, szOut, iLen, szNormalized.GetBuffer(iNewLen), iNewLen);		
		if (iNewLen <= 0)
		{
			szNormalized.ReleaseBuffer(0);
			return iLen;
		}
		szNormalized.ReleaseBuffer(iNewLen);
		szOut = szNormalized;
		return iNewLen;
#else
		return iLen;
#endif
	}
	else
	{		
		return -1;
	}	
}