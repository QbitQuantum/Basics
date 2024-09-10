	BOOL CDuiAutoComplete::SaveList(LPCTSTR pszFileName)
	{
		FILE* fp = _tfsopen(pszFileName, _T("wb"), _SH_DENYWR);
		if (fp == NULL)
			return FALSE;

		// Ð´ Unicode ±àÂë×Ö½ÚÐò mark 0xFEFF
		fputwc(0xFEFF, fp);

		for (int i = 0; i < m_sStringArrayMap.GetSize(); i++)
			_ftprintf(fp, _T("%s\r\n"), m_sStringArrayMap[i]);
		fclose(fp);
		return !ferror(fp);
	}