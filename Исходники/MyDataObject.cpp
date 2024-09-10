HRESULT __stdcall CMyDataObject::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppEnumFormatEtc)
{
	if (dwDirection == DATADIR_GET)
	{
		// Windows 2000 and newer only.
		return SHCreateStdEnumFmtEtc(1, &m_FormatEtc, ppEnumFormatEtc);
		//return CreateEnumFmtEtc(1,&m_FormatEtc,ppEnumFormatEtc);
	}
	else
	{
		return E_NOTIMPL;
	}
}