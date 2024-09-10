BOOL base_string::IsDigitalW(wstring wstrSrc)
{
	int nIndex = 0;
	size_t nPos = wstrSrc.find('.');
	if (wstrSrc.empty())
	{
		return FALSE;
	}
	else if (nPos == wstring::npos)
	{
		for (nIndex = 0; nIndex < wstrSrc.length(); nIndex++)
		{
			if (wstrSrc[nIndex] < '0' || wstrSrc[nIndex] > '9')
			{
				return FALSE;
			}
		}
	}
	else if (nPos == wstrSrc.length() - 1)
	{
		return FALSE;
	}
	else if (nPos != wstring::npos)
	{
		for (nIndex = 0; nIndex < nPos; nIndex++)
		{
			if (wstrSrc[nIndex] < '0' || wstrSrc[nIndex] > '9')
			{
				return FALSE;
			}
		}
		for (nIndex = nPos + 1; nIndex < wstrSrc.length(); nIndex++)
		{
			if (wstrSrc[nIndex] < '0' || wstrSrc[nIndex] > '9')
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}