void CAboutDlg::FillObjectVersion(LPCTSTR szProgID)
{
	CLSID cls;
	USES_CONVERSION;
	CLSIDFromProgID(T2W(szProgID), &cls);
	FillObjectVersion(cls);
}