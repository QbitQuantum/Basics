BOOL CCustomAutoComplete::SaveList(LPCTSTR pszFileName)
{
	FILE* fp = _tfsopen(pszFileName, _T("wb"), _SH_DENYWR);
	if (fp == NULL)
		return FALSE;

	// write Unicode byte-order mark 0xFEFF
	fputwc(0xFEFF, fp);

	for (int i = 0; i < m_asList.GetCount(); i++)
		_ftprintf(fp, _T("%s\r\n"), m_asList[i]);
	fclose(fp);
	return !ferror(fp);
}