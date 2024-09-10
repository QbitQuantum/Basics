BOOL CSbproAux::ReportError(CException* e)
{
	HWND hwnd = (HWND)m_sbpro.GetHWnd();
	if (hwnd != NULL)
	{
		SbproReportError re;
		memset(&re,0,sizeof(re));
		if (e->IsKindOf(RUNTIME_CLASS(COleException)))
		{
			re.scode = ((COleException*)e)->m_sc;
			return (BOOL)::SendMessage(hwnd,SB_MCM_REPORTERROR,0,(LPARAM)&re);
		}

		if (e->IsKindOf(RUNTIME_CLASS(COleDispatchException)))
		{
			USES_CONVERSION;
			COleDispatchException* ode = (COleDispatchException*)e;
			re.scode = 0;
			re.wCode = ode->m_wCode;
			re.lpszDescription = T2CA((LPCTSTR)ode->m_strDescription);
			re.lpszSource = T2CA((LPCTSTR)ode->m_strSource);
			re.dwHelpContext = ode->m_dwHelpContext;
			re.lpszHelpFile = T2CA((LPCTSTR)ode->m_strHelpFile);
			return (BOOL)::SendMessage(hwnd,SB_MCM_REPORTERROR,0,(LPARAM)&re);
		}
	}

	// this should never happen?
	e->ReportError();
	return FALSE;
}