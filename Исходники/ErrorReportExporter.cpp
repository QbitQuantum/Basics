BOOL CErrorReportExporter::Init(LPCTSTR szFileMappingName)
{
	m_sErrorMsg = _T("Unspecified error.");
		
	// Read crash information from the file mapping object.
	int nInit = m_CrashInfo.Init(szFileMappingName);
	if(nInit!=0)
	{
		m_sErrorMsg.Format(_T("Error reading crash info: %s"), m_CrashInfo.GetErrorMsg().GetBuffer(0));
		return FALSE;
	}
		
	SetProcessDefaultLayout(LAYOUT_RTL); 

	// Start crash info collection work assynchronously
	DoWorkAssync(COLLECT_CRASH_INFO);

	// Done.
	m_sErrorMsg = _T("Success.");
	return TRUE;
}