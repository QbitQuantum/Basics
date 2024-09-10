/**
* Download and install from a remote location using HTTP.
* @param url the url indicating the location of the widget.
* @param widget receives the constructed widget on success.
*/
STDMETHODIMP CBondiWidgetLibrary::RemoteInstall(BSTR url, IBondiWidget** widget)
{
	HRESULT hRes = S_OK;

	try
	{
		TCHAR appDataPath[MAX_PATH];
		WidgetUtils::GetAppFolder(NULL,appDataPath);

		TCHAR canonicalURL[1024];
		DWORD nSize = 1024;
		InternetCanonicalizeUrl(url, canonicalURL, &nSize, ICU_BROWSER_MODE);

		// Check for an internet connection.
		if (InternetAttemptConnect(0) != ERROR_SUCCESS)
			BONDI_RAISE_ERROR(E_BONDI_WIDGET_NO_INTERNET,_T("no internet connection found"));

		// Open a connection.
		HINTERNET hINet = InternetOpen(agentName,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,INTERNET_FLAG_NO_CACHE_WRITE);

		if (hINet != 0)
		{
			HANDLE hConnection = ConnectToNetwork(25);
			if (hConnection != NULL)
			{
				// Attempt to access the resource at the url.
				DWORD options = INTERNET_FLAG_NEED_FILE|INTERNET_FLAG_HYPERLINK|INTERNET_FLAG_RESYNCHRONIZE|INTERNET_FLAG_RELOAD;
				HINTERNET hFile = InternetOpenUrl( hINet, canonicalURL, NULL, 0, options, 0 );

				if (hFile != 0)
				{
					// Determine the file name to store the downloaded widget resource.
					TCHAR fName[MAX_PATH];
					_tsplitpath_s(url, NULL, 0, NULL, 0, fName, _MAX_FNAME, NULL, 0); 

					// Create the target local file.
					_bstr_t downloadPath = appDataPath + _bstr_t("\\") + _bstr_t(fName) + _bstr_t(".wgt");			
					HANDLE target = ::CreateFile(downloadPath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

					// Read chunks.
					BYTE buffer[1024];
					DWORD dwRead;
					while (::InternetReadFile( hFile, buffer, 1024, &dwRead ) )
					{
						if ( dwRead == 0 )
							break;

						::WriteFile(target,buffer,dwRead,&dwRead,NULL);
					}

					::CloseHandle(target);

					InternetCloseHandle(hFile);

					CComObject<CBondiWidget>* newWidget;
					BONDI_CHECK_ERROR(CComObject<CBondiWidget>::CreateInstance(&newWidget),(IBondiWidgetLibrary*)this);
					newWidget->AddRef();

					// Do the installation.
					_bstr_t locale("en");
					hRes = newWidget->Install(downloadPath,locale,VARIANT_FALSE,VARIANT_FALSE);
					BONDI_CHECK_ERROR(hRes,(IBondiWidget*)newWidget);					

					if (hRes == S_OK)
					{
						// Set the install URL.
						CComPtr<IBondiWidgetAppConfig> appConfig;
						BONDI_CHECK_ERROR(newWidget->get_AppSettings(&appConfig),(IBondiWidget*)newWidget);
						if (appConfig != NULL)
							BONDI_CHECK_ERROR(appConfig->PutBondiSetting(_T("bondi.installUri"),canonicalURL,VARIANT_TRUE),appConfig);

						newWidget->InitialiseAppSettings();

						// We've finished with the temporary downloaded resource.
						::DeleteFile(downloadPath);

						*widget = (IBondiWidget*)newWidget;
					}
					else
					{
						// Didn't install (probably because of an existing widget).
						*widget = NULL;
					}
				}
				else
				{				 
					DWORD err = GetLastError();
					BONDI_RAISE_ERROR(E_BONDI_WIDGET_URL_OPEN_FAILED,_T("couldn't open url: ") + CString(canonicalURL));
				}

#ifdef UNDER_CE
				ConnMgrReleaseConnection(hConnection,1);
				CloseHandle(hConnection);
#endif
			}

			InternetCloseHandle(hINet);
		}
		else
		{
			BONDI_RAISE_ERROR(E_BONDI_WIDGET_NO_INTERNET,_T("error opening internet connection"));
		}
	}
	catch (_com_error& err)
	{
		hRes = BONDI_SET_ERROR(err,"CBondiWidgetLibrary::RemoteInstall - COM exception");
	}
	catch (...)
	{
		hRes = BONDI_SET_ERROR(E_FAIL,"CBondiWidgetLibrary::RemoteInstall - C++ exception");
	}

	return hRes;
}