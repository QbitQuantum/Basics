BOOL CCmd_Delete::HandledCmdSpecificError(LPCTSTR errBuf, LPCTSTR errMsg)
{
	m_FatalError = TRUE;

    if( StrStr(errBuf, _T("use -f to force delete")))
	{
		CString m;
        m.FormatMessage(IDS_CANT_DELETE_PRIVELEGE_s, 
            CString(errBuf, StrStr(errBuf, _T("; use -f")) - errBuf ));
		TheApp()->StatusAdd( m, SV_ERROR);
		return m_FatalError;
	}

	if(StrStr(errBuf, _T("Can't delete client")) && StrStr(errBuf, _T("owned by")))
	{
		TheApp()->StatusAdd(LoadStringResource(IDS_CANT_DELETE_UNOWNED_CLIENT), SV_ERROR);
		return m_FatalError;
	}

	if(StrStr(errBuf, _T("Can't delete label")))
	{
		if(StrStr(errBuf, _T("owned by")))
			TheApp()->StatusAdd( LoadStringResource(IDS_CANT_DELETE_UNOWNED_LABEL), SV_ERROR);
		else
			TheApp()->StatusAdd(errMsg, SV_ERROR );
		return m_FatalError;
	}

	if(StrStr(errBuf, _T("Can't delete branch")))
	{
		if(StrStr(errBuf, _T("owned by")))
			TheApp()->StatusAdd( LoadStringResource(IDS_CANT_DELETE_UNOWNED_BRANCH), SV_ERROR);
		else
			TheApp()->StatusAdd(errMsg, SV_ERROR);
		return m_FatalError;
	}

	if (( StrStr(errBuf, _T("don't have permission"))) 
	 || ( StrStr(errBuf, _T("is locked and can't be deleted"))))

	{
		TheApp()->StatusAdd( errMsg, SV_ERROR );
		return m_FatalError;
	}

	m_FatalError = FALSE;
	return m_FatalError;
}