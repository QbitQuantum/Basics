VOID CLoginProcess::RenderPatch(int nLoopTime)
{	
	RECT tRect;
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
	//
	Clear((DWORD)RGB(0,0,0));

/*
	// Go Login Without Connection
	m_Progress = PRG_INTRO;
	m_fIsConnected	= CONNECT_SUCCESS;
	g_xMainWnd.ResetDXG(_SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
*/

	if(pPatch->m_bEndPatch == TRUE)//GetFtpFiles()==0l)	// Patch가 종료 되었으면
	{
		
		if(pPatch->m_bPatched == TRUE)	// Patch 되었으면 종료
		{
			delete pPatch;
			char PatchName[1024];
			ZeroMemory(PatchName,1024);
			GetCurrentDirectory(1024,PatchName);
			strcat(PatchName,MIR2_PATCH_FILE_NAME);
			//m_Progress = PRG_QUIT;
      m_Progress = PRG_INTRO;
			ShellExecute(NULL,"open",PatchName,NULL,NULL,SW_SHOWNORMAL);
			// 실행을 종료하고 외부 Patch 프로그램을 실행시킨다.
		}
		else
		{
			// 패치 한것이 없으면
			delete pPatch;

			g_xClientSocket.ConnectToServer(g_xMainWnd.GetSafehWnd(), m_szServerIP, m_nServerPort);
			m_Progress = PRG_INTRO;


			// Full Screen 으로 전환
			g_xMainWnd.ResetDXG(640, 480, _SCREEN_BPP, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
//			g_xMainWnd.ResetDXG(640, 480, _SCREEN_BPP, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
			SETRECT(tRect, SCR_LEFT, SCR_TOP, SCR_RIGHT, SCR_BOTTOM );
		}
	}
	else
	{
		// 계속 패치 해야하면
		pPatch->GetFtpFiles();
	}

	if(m_xMsgBox.IsActive())
	{
		HINSTANCE hLib;
		hLib = LoadLibrary(MESSAGE_DLL_1);
		SetErrorMessage(300,m_szErrorMsg);		// 헤당 Error 메시지 찾기
		FreeLibrary(hLib);
		MessageBox(g_xMainWnd.GetSafehWnd(),m_szErrorMsg,"Error",MB_OK);
	}
}