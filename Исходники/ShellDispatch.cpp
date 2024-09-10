static int MyShellDispatch_ShellDispatchProc(const shell_dispatch_handler_t handler, void *const data)
{
	int iSuccess = SHELL_DISPATCH_FAILED;

	IShellWindows *psw = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&psw));
	if(SUCCEEDED(hr))
	{
		HWND desktopHwnd = 0;
		IDispatch* pdisp = NULL;
		variant_t vEmpty;
		if(S_OK == psw->FindWindowSW(vEmpty, vEmpty, SWC_DESKTOP, (long*)&desktopHwnd, SWFO_NEEDDISPATCH, &pdisp))
		{
			if(VALID_HANDLE(desktopHwnd))
			{
				IShellBrowser *psb;
				hr = IUnknown_QueryService(pdisp, SID_STopLevelBrowser, IID_PPV_ARGS(&psb));
				if(SUCCEEDED(hr))
				{
					IShellView *psv = NULL;
					hr = psb->QueryActiveShellView(&psv);
					if(SUCCEEDED(hr))
					{
						IDispatch *pdispBackground = NULL;
						HRESULT hr = psv->GetItemObject(SVGIO_BACKGROUND, IID_PPV_ARGS(&pdispBackground));
						if(SUCCEEDED(hr))
						{
							MyShellDispatch_AllowSetForegroundWindow(desktopHwnd);
							IShellFolderViewDual *psfvd = NULL;
							HRESULT hr = pdispBackground->QueryInterface(IID_PPV_ARGS(&psfvd));
							if(SUCCEEDED(hr))
							{
								IDispatch *pdisp = NULL;
								hr = psfvd->get_Application(&pdisp);
								if(SUCCEEDED(hr))
								{
									IShellDispatch2 *pShellDispatch;
									hr = pdisp->QueryInterface(IID_PPV_ARGS(&pShellDispatch));
									if(SUCCEEDED(hr))
									{
										iSuccess = handler(pShellDispatch, data);
									}
									RELEASE_OBJ(pdisp);
								}
								RELEASE_OBJ(psfvd);
							}
							RELEASE_OBJ(pdispBackground);
						}
						RELEASE_OBJ(psv);
					}
					RELEASE_OBJ(psb);
				}
			}
			RELEASE_OBJ(pdisp);
		}
		RELEASE_OBJ(psw);
	}

	return iSuccess;
}