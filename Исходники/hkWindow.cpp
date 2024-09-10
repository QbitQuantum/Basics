HWND WINAPI OnGetAncestor(HWND hWnd, UINT gaFlags)
{
	//typedef HWND (WINAPI* OnGetAncestor_t)(HWND hWnd, UINT gaFlags);
	ORIGINAL_EX(GetAncestor);
	HWND lhRc = NULL;

	#ifdef LOG_GETANCESTOR
	if (ghAttachGuiClient)
	{
		wchar_t szInfo[1024];
		getWindowInfo(hWnd, szInfo);
		lstrcat(szInfo, L"\n");
		DebugString(szInfo);
	}
	#endif

	//if (ghConEmuWndDC && hWnd == ghConEmuWndDC)
	//{
	//	hWnd = ghConEmuWnd;
	//}
	if (ghConEmuWndDC)
	{
		#ifdef _DEBUG
		if ((GetKeyState(VK_CAPITAL) & 1))
		{
			int nDbg = 0;
		}
		#endif

		if (ghAttachGuiClient)
		{
			// Обмануть GUI-клиента, пусть он думает, что он "сверху"
			if (hWnd == ghAttachGuiClient || hWnd == ghConEmuWndDC)
			{
				hWnd = ghConEmuWnd;
			}
			#if 0
			else
			{
				wchar_t szName[255];
				GetClassName(hWnd, szName, countof(szName));
				if (wcsncmp(szName, L"WindowsForms", 12) == 0)
				{
					GetWindowText(hWnd, szName, countof(szName));
					if (wcsncmp(szName, L"toolStrip", 8) == 0 || wcsncmp(szName, L"menuStrip", 8) == 0)
					{
						hWnd = ghConEmuWndDC;
					}
				}
			}
			#endif
		}
		else if (hWnd == ghConEmuWndDC)
		{
			hWnd = ghConEmuWnd;
		}
	}

	if (F(GetAncestor))
	{
		lhRc = F(GetAncestor)(hWnd, gaFlags);

		if (ghAttachGuiClient && (gaFlags == GA_ROOTOWNER || gaFlags == GA_ROOT) && lhRc == ghConEmuWnd)
		{
			lhRc = ghAttachGuiClient;
		}
	}

	_ASSERTRESULT(lhRc);
	return lhRc;
}