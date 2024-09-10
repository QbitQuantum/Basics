DWORD WINAPI ThreadFunc(LPVOID lpram){


	g_mainDlg = new CMainDataDlg;
	g_mainDlg->DoModal();
	delete g_mainDlg;
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);

	return TRUE;

}