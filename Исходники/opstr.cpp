CStringA ConvertUnicodeToString(LPCWSTR pSrc)
{
	CStringA strResult;
	UINT nCodePage = CP_GB18030;
	if (!IsValidCodePage(CP_GB18030))
	{
		nCodePage = _AtlGetConversionACP();
	}
	int iBytes = ::WideCharToMultiByte(nCodePage, 0, pSrc, -1, NULL, 0, NULL, NULL);
	if (iBytes)
	{
		iBytes = ::WideCharToMultiByte(nCodePage, 0, pSrc, -1, strResult.GetBuffer(iBytes), iBytes, NULL, NULL);
		strResult.GetBuffer()[iBytes] = 0;
		strResult.ReleaseBufferSetLength(iBytes);
	}
	return strResult;
}