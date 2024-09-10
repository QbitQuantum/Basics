/*!
@brief Gets Integration level of the given process in Vista. 
In the older OS assumes the integration level is equal to SECURITY_MANDATORY_HIGH_RID

The function opens the process for all access and opens its token for all access. 
Then it extracts token information and closes the handles.
@param[in] dwProcessId ID of the process to operate
@param[out] pdwProcessIL pointer to write the value
@return HRESULT
@retval <return value> { description }
@remarks Function check for OS version by querying the presence of Kernel32.GetProductInfo function. 
This way is used due to the function is called from InstallShield12 script, so GetVersionEx returns incorrect value.
@todo restrict access rights when quering for tokens
*/
inline HRESULT GetProcessIL(DWORD dwProcessId, LPDWORD pdwProcessIL)
{
	HRESULT hr=S_OK;
	if(!pdwProcessIL)
		hr=E_INVALIDARG;
	if(SUCCEEDED(hr))
	{
		bool bVista=false;
		{
			// When the function is called from IS12, GetVersionEx returns dwMajorVersion=5 on Vista!
			HMODULE hmodKernel32=LoadLibraryA("Kernel32");
			if(hmodKernel32 && GetProcAddress(hmodKernel32, "GetProductInfo"))
				bVista=true;
			if(hmodKernel32) FreeLibrary(hmodKernel32);
		}

		DWORD dwIL=SECURITY_MANDATORY_HIGH_RID;
		if(bVista)
		{//Vista
			HANDLE hToken=NULL;
			HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
			if(hProcess)
			{
				if(OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken))
				{
					PTOKEN_MANDATORY_LABEL pTIL=NULL;
					DWORD dwSize=0;
					if (!GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &dwSize) 
						&& ERROR_INSUFFICIENT_BUFFER==GetLastError() && dwSize)
						pTIL=(PTOKEN_MANDATORY_LABEL)HeapAlloc(GetProcessHeap(), 0, dwSize);

					if(pTIL && GetTokenInformation(hToken, TokenIntegrityLevel, pTIL, dwSize, &dwSize))
					{
						LPBYTE lpb=GetSidSubAuthorityCount(pTIL->Label.Sid);
						if(lpb)
							dwIL = *GetSidSubAuthority(pTIL->Label.Sid, *lpb-1);
						else
							hr=E_UNEXPECTED;
					}
					if(pTIL)
						HeapFree(GetProcessHeap(), 0, pTIL);
					CloseHandle(hToken);
				}//if(OpenProcessToken(...))
				CloseHandle(hProcess);
			}//if(hProcess)
		}//if(bVista)
		if(SUCCEEDED(hr))
			*pdwProcessIL=dwIL;
	}//if(SUCCEEDED(hr))
	return hr;
}