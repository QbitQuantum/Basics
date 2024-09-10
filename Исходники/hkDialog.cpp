HWND WINAPI OnCreateDialogParamA(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
	//typedef HWND (WINAPI* OnCreateDialogParamA_t)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
	ORIGINALFASTEX(CreateDialogParamA,NULL);
	HWND hWnd = NULL;
	BOOL bAttachGui = FALSE, bStyleHidden = FALSE;
	LPCDLGTEMPLATE lpTemplate = NULL;
	DWORD lStyle = 0; //lpTemplate ? lpTemplate->style : 0;
	DWORD lStyleEx = 0; //lpTemplate ? lpTemplate->dwExtendedStyle : 0;

	// Загрузить ресурс диалога, и глянуть его параметры lStyle/lStyleEx
	HRSRC hDlgSrc = FindResourceA(hInstance, lpTemplateName, /*RT_DIALOG*/MAKEINTRESOURCEA(5));
	if (hDlgSrc)
	{
		HGLOBAL hDlgHnd = LoadResource(hInstance, hDlgSrc);
		if (hDlgHnd)
		{
			lpTemplate = (LPCDLGTEMPLATE)LockResource(hDlgHnd);
			if (lpTemplate)
			{
				lStyle = lpTemplate ? lpTemplate->style : 0;
				lStyleEx = lpTemplate ? lpTemplate->dwExtendedStyle : 0;
			}
		}
	}

	if ((!lpTemplate || CheckCanCreateWindow((LPSTR)32770, NULL, lStyle, lStyleEx, hWndParent, bAttachGui, bStyleHidden))
		&& F(CreateDialogParamA) != NULL)
	{
		//if (bAttachGui)
		//{
		//	x = grcConEmuClient.left; y = grcConEmuClient.top;
		//	nWidth = grcConEmuClient.right - grcConEmuClient.left; nHeight = grcConEmuClient.bottom - grcConEmuClient.top;
		//}

		hWnd = F(CreateDialogParamA)(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
		DWORD dwErr = GetLastError();

		if (hWnd && bAttachGui)
		{
			OnGuiWindowAttached(hWnd, NULL, (LPCSTR)32770, NULL, lStyle, lStyleEx, bStyleHidden);

			SetLastError(dwErr);
		}
	}

	return hWnd;
}