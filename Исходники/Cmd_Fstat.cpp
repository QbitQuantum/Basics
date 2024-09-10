BOOL CCmd_Fstat::HandledCmdSpecificError(LPCTSTR errBuf, LPCTSTR errMsg)
{
    if ((StrStr(errBuf, _T(" - file(s) not in client view")))
	 ||	(StrStr(errBuf, _T(" - protected namespace - access denied")))
	 || (m_bWorking && StrStr(errBuf, _T(" - file(s) not opened on this client"))))
	{
        return TRUE;
	}
    else if ((GET_P4REGPTR( )->ShowEntireDepot( ) > SDF_DEPOT)
		  && (StrStr(errBuf, _T(" - no mappings in client view"))))
	{
		m_ErrorList.AddHead(errBuf);
        return TRUE;
	}
	else if ( StrStr(errBuf, _T("no such file") )  )
	{
		TheApp()->StatusAdd( LoadStringResource(IDS_NO_FILES_UNDER_FOLDER), SV_DEBUG );  
		return TRUE ; 
	}
	else if ( StrStr(errBuf, _T(" database access failed.") )  )
	{
		m_FatalError = TRUE;
		return FALSE;
	}

	return StrStr(errBuf, _T("up-to-date.") ) != 0;
}