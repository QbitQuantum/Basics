VOID CDeskIconManager::MouseRClick(int nX,int nY)
{
	//个性化
	//rundll32.exe shell32.dll,Control_RunDLL desk.cpl,1,2
	
	HMODULE hShellMod = LoadLibrary(L"shell32.dll");

	if (hShellMod)
	{
		typedef void ( WINAPI *TypeRunDll32FunW)(HWND hwnd, HINSTANCE hinst, LPWSTR lpszCmdLine, int nCmdShow);

		TypeRunDll32FunW pFun = (TypeRunDll32FunW)::GetProcAddress(hShellMod,"Control_RunDLLW");
		if (pFun)
		{
			pFun(m_wndShow,NULL,L"desk.cpl,1,2",SW_SHOW);
		}
	}


 	CMenu Menu;
 	Menu.CreatePopupMenu();
 	Menu.AppendMenu(MF_STRING,0,L"刷新(&E)");
	Menu.AppendMenu(MF_STRING,0,L"个性化(&R)");
	//Menu.AppendMenu(MF_STRING,0,L"个性化(&R)");
 	::TrackPopupMenu(Menu.m_hMenu,TPM_LEFTALIGN|TPM_TOPALIGN,nX,nY,0,m_wndShow,NULL);
	
}