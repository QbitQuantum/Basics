BOOL CCapDownload::checkOcsAgentSetupResult()
{
	CString csFile, csCode = ERR_DONE_FAILED, csID;
	CStdioFile myFile;

	csFile.Format(_T("%s\\%s"), getDownloadFolder(), OCS_AGENT_SETUP_DONE);
	if (!fileExists(csFile))
		// No OCS Agent Setup done file
		return TRUE;
	m_pLogger->log(LOG_PRIORITY_DEBUG, _T("DOWNLOAD => Found OCS Inventory Agent Setup result file <%s>"), csFile);
	// Open OCS Agent Setup done file to read exit code and package ID
	try
	{
		if (!myFile.Open(csFile, CFile::modeRead | CFile::typeText | CFile::shareDenyNone))
			return FALSE;
		// First line contains result code and seconf line contains package ID
		myFile.ReadString(csCode);
		myFile.ReadString(csID);
		myFile.Close();
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		myFile.Abort();
		m_pLogger->log(LOG_PRIORITY_ERROR, _T("DOWNLOAD => Failed reading OCS Inventory Agent Setup result file <%s>"), csFile);
		return FALSE;
	}
	if (csID.IsEmpty())
	{
		// Upgrading from agent 1.X or previous to 2.0.0.22 ?
		m_pLogger->log(LOG_PRIORITY_ERROR, _T("DOWNLOAD => Found result code <%s> for OCS Inventory Agent Setup package but no package ID specified, so remove all packages to avoid running Agent setup in loop !"), csCode);
		COptDownloadPackage::cleanAll();
		return FALSE;
	}
	// All information available => copy result file to Package directory
	csFile.Format(_T("%s\\%s\\%s"), getDownloadFolder(), csID, OCS_DOWNLOAD_DONE);
	if (!CopyFile(myFile.GetFilePath(), csFile, FALSE))
	{
		m_pLogger->log(LOG_PRIORITY_ERROR, _T("DOWNLOAD => Failed to copy result code for OCS Inventory Agent Setup package to file <%s>"), csFile);
		return FALSE;
	}
	DeleteFile(myFile.GetFilePath());
	m_pLogger->log(LOG_PRIORITY_NOTICE, _T("DOWNLOAD => Validated result code <%s> for OCS Inventory Agent Setup package <%s>"), csCode, csID);
	return TRUE;
}