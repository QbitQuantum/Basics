static int ShellExecAsUser_ShellDispatchProc(const TCHAR *pcOperation, const TCHAR *pcFileName, const TCHAR *pcParameters, const HWND parentHwnd)
{
	int iSuccess = SHELLEXECASUSER_ERROR_FAILED;

	IShellWindows *psw = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&psw));
	if(SUCCEEDED(hr))
	{
		HWND hwnd = 0;
		IDispatch* pdisp = NULL;
		variant_t vEmpty;
		if(S_OK == psw->FindWindowSW(vEmpty, vEmpty, SWC_DESKTOP, (long*)&hwnd, SWFO_NEEDDISPATCH, &pdisp))
		{
			if((hwnd != NULL) && (hwnd != INVALID_HANDLE_VALUE))
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
						if (SUCCEEDED(hr))
						{
							IShellFolderViewDual *psfvd = NULL;
							hr = pdispBackground->QueryInterface(IID_PPV_ARGS(&psfvd));
							if (SUCCEEDED(hr))
							{
								IDispatch *pdisp = NULL;
								hr = psfvd->get_Application(&pdisp);
								if (SUCCEEDED(hr))
								{
									IShellDispatch2 *psd;
									hr = pdisp->QueryInterface(IID_PPV_ARGS(&psd));
									if(SUCCEEDED(hr))
									{
										DispatchPendingMessages(125);
										variant_t verb(pcOperation);
										variant_t file(pcFileName);
										variant_t para(pcParameters);
										variant_t show(SW_SHOWNORMAL);
										hr = psd->ShellExecute(file, para, vEmpty, verb, show);
										if(SUCCEEDED(hr))
										{
											iSuccess = SHELLEXECASUSER_ERROR_SUCCESS;
										}
										psd->Release();
										psd = NULL;
									}
									pdisp->Release();
									pdisp = NULL;
								}
							}
							pdispBackground->Release();
							pdispBackground = NULL;
						}
						psv->Release();
						psv = NULL;
					}
					psb->Release();
					psb = NULL;
				}
			}
			pdisp->Release();
			pdisp = NULL;
		}
		psw->Release();
		psw = NULL;
	}

	return iSuccess;
}