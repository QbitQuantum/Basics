LRESULT CDlgChVMask::OnDlgFree(WPARAM wParam,LPARAM lParam)
{
	CString strmsg;
	KILLTIMER(m_timerid);
	if(m_hchann != -1)
	{
		strmsg.LoadString(IDS_STRING259);
		g_SerParam->m_txtMsginfo.SetWindowText(strmsg);
		VSNET_ClientStop(m_hchann);
		m_hchann = -1;
		g_SerParam->m_txtMsginfo.SetWindowText("");
	}
	return 0;
}