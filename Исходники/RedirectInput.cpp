// Function name	: RedirectInputThread
// Description	    : 
// Return type		: void 
// Argument         : RedirectInputThreadArg *arg
void RedirectInputThread(RedirectInputThreadArg *arg)
{
	IRemoteShell *pLaunch=NULL;
	HRESULT hr=S_OK;
	HANDLE hObject[2];
	long error=0;
	BSTR berror_msg;
	DWORD ret_val;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	berror_msg = SysAllocString(L"");
	CoGetInterfaceAndReleaseStream (*arg->ppStream, IID_IRemoteShell, (void**) &pLaunch);
	delete arg->ppStream;

	DWORD dwThreadID;
	HANDLE hRSIThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadStdinThread, NULL, 0, &dwThreadID);

	hObject[0] = arg->hEvent;
	hObject[1] = g_hBufferEvent1;

	berror_msg = SysAllocString(L"");
	while (true)
	{
		ret_val = WaitForMultipleObjects(2, hObject, FALSE, INFINITE);
		if (ret_val == WAIT_OBJECT_0+1)
		{
			if (g_num_read > 0)
			{
				SAFEARRAYBOUND bound;
				VARIANT vInput;
				void *pBuf;

				VariantInit(&vInput);
				bound.lLbound = 0;
				bound.cElements = g_num_read;
				vInput.vt = VT_UI1 | VT_ARRAY;
				vInput.parray = SafeArrayCreate(VT_UI1, 1, &bound);

				SafeArrayAccessData(vInput.parray, &pBuf);
				memcpy(pBuf, g_pBuffer, g_num_read);
				SafeArrayUnaccessData(vInput.parray);

				error = 0;
				hr = pLaunch->PutProcessInput(vInput, &error, &berror_msg);
				if (FAILED(hr))
				{
					VariantClear(&vInput);
					printf("PutInteractiveInput failed: %d\n", hr);
					PrintError(hr);
					break;
				}
				if (error)
				{
					VariantClear(&vInput);
					if (wcslen(berror_msg) < 1)
						wprintf(L"PutInteractiveInput failed: %d %s\n", error, berror_msg);
					else
						wprintf(L"PutInteractiveInput failed: %s\n", berror_msg);
					break;
				}
				VariantClear(&vInput);
			}
			ResetEvent(g_hBufferEvent1);
			SetEvent(g_hBufferEvent2);
		}
		else
		{
			//printf("g_hFinishedEvent signalled\n");
		    TerminateThread(hRSIThread, 0);
			break;
		}
	}

	pLaunch->Release();
	CoUninitialize();
}