BOOL ClianliankanDlg::GetChessBase()
{
	//m_lpChess = (LPVOID)0x129f78;
// 	OSVERSIONINFOEX  VerInfo;
// 	VerInfo.dwOSVersionInfoSize = sizeof(VerInfo);
// 	if (!GetVersionEx((OSVERSIONINFO *)&VerInfo))
// 	{
// 		return FALSE;
// 	}
// 	if (VerInfo.dwMajorVersion != 6)
// 	{
// 		return FALSE;
// 	}
// 	switch (VerInfo.dwMinorVersion)
// 	{
// 	case 1:
// 		//win7
// 		m_lpChess = (LPVOID)0x129f78;
// 		break;
// 	case 2:
// 		//win8
// 		m_lpChess = (LPVOID)0x189f7c;
// 		break;
// 	default:
// 		break;
// 	}
	if (IsOS(OS_WOW6432))
	{
		m_lpChess = (LPVOID)0x189f7c;
	}
	else
	{
		m_lpChess = (LPVOID)0x129f78;
	}
	return TRUE;
}