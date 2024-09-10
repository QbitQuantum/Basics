VOID CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook,
				DWORD event,
				HWND hwnd,
				LONG idObject,
				LONG idChild,
				DWORD dwEventThread,
				DWORD dwmsEventTime)
{
	IAccessible* pAcc = NULL;
	VARIANT varChild;
	HRESULT hr = AccessibleObjectFromEvent(hwnd, idObject, idChild, &pAcc, &varChild);
	if ((hr == S_OK) && (pAcc != NULL)) {
		BSTR bstrName, bstrValue;
		
		pAcc->get_accValue(varChild, &bstrValue);
		pAcc->get_accName(varChild, &bstrName);

		char className[50];
		GetClassNameA(hwnd, className, 50);

		if ((strcmp(className, "Chrome_WidgetWin_1") == 0) && (wcscmp(bstrName, L"Address and search bar") == 0)) {
			SendMessage(ghWnd, WM_UPDATECAREPOS, NULL, (WPARAM)(bstrValue));//LPCWSTR
			printf("URL change: %ls\n", bstrValue);
		}
		pAcc->Release();
	}

	return;
}