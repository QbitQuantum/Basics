wchar_t * UT_GetDefaultPrinterName()
{
	UT_uint32 iBufferSize = 128; // will become 2x bigger immediately in the loop
	wchar_t * pPrinterName = NULL; 
	DWORD rc;
	
	do
	{
		iBufferSize *= 2;

		if(pPrinterName)
			g_free(pPrinterName);
		
		pPrinterName = (wchar_t *) UT_calloc(sizeof(wchar_t),iBufferSize);
		UT_return_val_if_fail( pPrinterName, NULL );
		
		// the method of obtaining the name is version specific ...
		OSVERSIONINFOW osvi;
		DWORD iNeeded, iReturned, iBuffSize;
		LPPRINTER_INFO_5W pPrinterInfo;
		wchar_t* p;

		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
		GetVersionExW(&osvi);

		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
		{
			// get size of the buffer needed to call enum printers
			if (!EnumPrintersW(PRINTER_ENUM_DEFAULT,NULL,5,NULL,0,&iNeeded,&iReturned))
			{
				if ((rc = GetLastError()) != ERROR_INSUFFICIENT_BUFFER)
				{
					return NULL;
				}
			}

			// allocate the buffer
			if ((pPrinterInfo = (LPPRINTER_INFO_5W)LocalAlloc(LPTR,iNeeded)) == NULL)
			{
				rc = GetLastError();
			}
			else
			{
				// now get the default printer
				if (!EnumPrintersW(PRINTER_ENUM_DEFAULT,NULL,5,
								  (LPBYTE) pPrinterInfo,iNeeded,&iNeeded,&iReturned))
				{
					rc = GetLastError();
				}
				else
				{
					if (iReturned > 0)
					{
						// here we copy the name to our own buffer
						if ((DWORD) wcslen(pPrinterInfo->pPrinterName) > iBufferSize-1)
						{
							rc = ERROR_INSUFFICIENT_BUFFER;
						}
						else
						{
							wcscpy(pPrinterName,pPrinterInfo->pPrinterName);
							rc = ERROR_SUCCESS;
						}
					}
					else
					{
						*pPrinterName = '0';
						rc = ERROR_SUCCESS;
					}
				}

				LocalFree(pPrinterInfo);
			}
		}
		else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			if (osvi.dwMajorVersion >= 5) /* Windows 2000 or later */
			{
				iBuffSize = iBufferSize;

				HMODULE hWinSpool = LoadLibraryW(L"winspool.drv");
				if (!hWinSpool)
					return NULL;

				HRESULT (WINAPI * fnGetDefaultPrinter)(LPWSTR, LPDWORD) =
					(HRESULT (WINAPI * )(LPWSTR, LPDWORD)) GetProcAddress(hWinSpool, GETDEFAULTPRINTER);
				
				if (!fnGetDefaultPrinter)
				{
					FreeLibrary(hWinSpool);
					return NULL;
				}

                bool i =false;
				if (!fnGetDefaultPrinter(pPrinterName,&iBuffSize))
                        i = true;
                         
                if(i)
					rc = GetLastError();
				else
					rc = ERROR_SUCCESS;

				FreeLibrary(hWinSpool);
			}
			else /* Windows NT 4.0 or earlier */
			{
				if (GetProfileStringW(L"windows",L"device",L"",pPrinterName,iBufferSize) == iBufferSize-1)
				{
					rc = ERROR_INSUFFICIENT_BUFFER;
				}
				else
				{
					p = pPrinterName;
					while (*p != '0' && *p !=L',')
						++p;
					*p = '0';

					rc = ERROR_SUCCESS;
				}
			}
		}
	}
	while (rc == ERROR_INSUFFICIENT_BUFFER);
	
	return pPrinterName;
}