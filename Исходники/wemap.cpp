int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR    lpCmdLine,
				   int       nCmdShow)
{
 hWnd_WEMAP = 0;
 hWnd_cid_gui = 0;
 hWnd_navitel = 0;
 hWndEdit = 0;
 hWnd_self = 0;
 hWnd_last = 0;


	fname = "\\Storage Card\\wemap\\wemap_WinMain.txt";
	fnamew = "\\Storage Card\\wemap\\Windows.txt";
	MSG msg;
	FILE * pFileTXT;
	Angle = DMDO_180;

	pFileTXT = fopen (fname,"a");

	UINT MS  = RegisterWindowMessageW(L"Private End Route Voice");
	fprintf (pFileTXT, "Private End Route Voice - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Start Route Voice");
	fprintf (pFileTXT, "Private Start Route Voice - %d\n", MS);

	MS = RegisterWindowMessageW(L"Private Close LCN_Upgrade Process");
	fprintf (pFileTXT, "Private Close LCN_Upgrade Process - %d\n", MS);	


	MS = RegisterWindowMessageW(L"Private Trip Info");
	fprintf (pFileTXT, "Private Trip Info - %d\n", MS);

	MS = RegisterWindowMessageW(L"Private Navi Start");
	fprintf (pFileTXT, "Private Navi Start - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Navi Closed");
	fprintf (pFileTXT, "Private Navi Closed - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Navi Destroyed");
	fprintf (pFileTXT, "Private Navi Destroyed - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Navi Exit");
	fprintf (pFileTXT, "Private Navi Exit - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Navi Volume");
	fprintf (pFileTXT, "Private Navi Volume - %d\n", MS);


	MS = RegisterWindowMessageW(L"Private Navi Button Down");
	fprintf (pFileTXT, "Private Navi Button Down - %d\n", MS);


	MS = RegisterWindowMessageW(L"Private Gps Ver Request");
	fprintf (pFileTXT, "Private Gps Ver Request - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Gps Ver Reply");
	fprintf (pFileTXT, "Private Gps Ver Reply - %d\n", MS);

	MS = RegisterWindowMessageW(L"Private TPEG Request");
	fprintf (pFileTXT, "Private TPEG Request - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private TPEG Reply");
	fprintf (pFileTXT, "Private TPEG Reply - %d\n", MS);

	MS = RegisterWindowMessageW(L"Private Gps Speed S12");
	fprintf (pFileTXT, "Private Gps Speed S12 - %d\n", MS);

	MS = RegisterWindowMessageW(L"Private Go To Main Dialog");
	fprintf (pFileTXT, "Private Go To Main Dialog - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Go To Setting Dialog");
	fprintf (pFileTXT, "Private Go To Setting Dialog - %d\n", MS);

	MS = RegisterWindowMessageW(L"Private Request Light Status");
	fprintf (pFileTXT, "Private Request Light Status - %d\n", MS);

	MS = RegisterWindowMessageW(L"UK SA Message Received");
	fprintf (pFileTXT, "UK SA Message Received - %d\n", MS);
	MS = RegisterWindowMessageW(L"UK Abort SA Client");
	fprintf (pFileTXT, "UK Abort SA Client - %d\n", MS);

	PrivateModeChange = RegisterWindowMessageW(L"Private Mode Change");
	fprintf (pFileTXT, "Private Mode Change - %d\n", PrivateModeChange);

	MS = RegisterWindowMessageW(L"Private Light Off");
	fprintf (pFileTXT, "Private Light Off - %d\n", MS);
	MS = RegisterWindowMessageW(L"Private Light On");
	fprintf (pFileTXT, "Private Light On - %d\n", MS);

	fclose (pFileTXT);


	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WEMAP));
	int  ret;
	int i;
	i = 0;
	ret = 1;
	while (ret)
	{
		while (!PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) 
		{
			if (i++>1000)
			{
				if ((hWnd_navitel<=0) || (hWnd_WEMAP<=0) || (hWnd_cid_gui<=0))
					EnumWindows( enum_proc, (LPARAM)"Ѕлокнот" );
				i=0;

			}
		}
		ret = GetMessage(&msg, NULL, NULL, NULL);

		SYSTEMTIME st;
		GetLocalTime(&st);
		pFileTXT = fopen (fname,"a");
		fprintf(pFileTXT, "---> Date: [%02d, %02d, %d]  Time: [%02d:%02d:%02d] " ,st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
		fprintf (pFileTXT, " wnd(%d) msg(%d) wParam(%d-%d) lParam(%d-%d) \n", msg.hwnd,msg.message,LOWORD(msg.wParam), HIWORD(msg.wParam),LOWORD(msg.lParam), HIWORD(msg.lParam));

		fclose (pFileTXT);

			
		if(  ret != -1 ) 
		{
			//else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (msg.message==PrivateModeChange)
			{
				pFileTXT = fopen (fname,"a");
				int wmId;
				wmId    = LOWORD(msg.wParam);
				
				if (wmId==1)
				{
					if (hWnd_navitel>0)
					{
						fprintf (pFileTXT, " Show Navitel \n");
						ShowWindow(hWnd_navitel,SW_SHOW);
						SetForegroundWindow(hWnd_navitel);
						set_rotation(true);
						UpdateWindow(hWnd_navitel);

					} else 
					{
						if (hWnd_WEMAP>0)
						{
							fprintf (pFileTXT, " Show WEMAP \n");
							set_rotation(true);
						}
					}

				} else
				{
					if ((hWnd_navitel>0) || (hWnd_WEMAP>0))
						if (wmId!=5)
						{
							fprintf (pFileTXT, " Hide Navitel(WEMAP) \n");
							set_rotation(false);
							if (hWnd_navitel>0)
								ShowWindow(hWnd_navitel,SW_HIDE);
							else
								ShowWindow(hWnd_WEMAP,SW_HIDE);
							ShowWindow(hWnd_cid_gui,SW_SHOW);
						}
				}
				fclose (pFileTXT);
			}
		}
	}
	return( ret );

}