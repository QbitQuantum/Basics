BOOL CXTPPropertyGridItemDate::ParseDateTime(COleDateTime& dt, LPCTSTR strValue)
{
	if (m_strFormat.IsEmpty())
		return FALSE;

	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(SYSTEMTIME));

	WORD* ptrDate[3] = {0, 0, 0};
	int nResult[3] = {0, 0, 0};

	CString strFormat(m_strFormat);
	strFormat.MakeLower();

	int nIndex = -1, i = 0;

	for (i = 0; i < 3; i++)
	{
		nIndex = strFormat.Find(_T('%'), nIndex + 1);

		if (nIndex == -1 || nIndex == strFormat.GetLength() - 1)
			return FALSE;

		switch (strFormat[nIndex + 1])
		{
			case _T('d'):
				ptrDate[i] = &sysTime.wDay;
				break;

			case _T('y'):
				ptrDate[i] = &sysTime.wYear;
				break;

			case _T('m'):
			case _T('b'):
				ptrDate[i] = &sysTime.wMonth;
				break;

			default:
				return FALSE;
		}

		strFormat.SetAt(nIndex + 1, _T('d'));
	}

	if (SCANF_S(strValue, strFormat, &nResult[0], &nResult[1], &nResult[2]) != 3)
		return FALSE;

	for (i = 0; i < 3; i++)
	{
		if (!ptrDate[i])
			return FALSE;

		*ptrDate[i] = (WORD)nResult[i];
	}

	dt = sysTime;
	return dt.GetStatus() == COleDateTime::valid;
}