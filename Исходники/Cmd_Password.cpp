void CCmd_Password::OnOutputInfo(char level, LPCTSTR data, LPCTSTR msg)
{
	if(StrStr(data, _T("Password updated")))
		TheApp()->StatusAdd( msg, SV_COMPLETION );
	else
	{
		m_ErrorTxt = StrCmp(data, _T("Password not changed.")) ? msg : data;
		CP4Command::OnOutputInfo(level, data, msg);
	}
}