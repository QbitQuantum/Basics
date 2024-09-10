//fast. doesn't check for server-side date.
HRESULT CInternetFileManagerObject::GetFileComplex(BSTR bstrURL, BSTR *pbstrFinalURL, 
												   BSTR *pbstrFinalPath)
{
	char szPath[INTERNET_MAX_PATH_LENGTH];
	BOOL bRetVal;
	char cinfo[MAX_CACHE_ENTRY_INFO_SIZE];
	HRESULT hr = S_OK;
	CString strFullURL, strFilename, strExtension;
	ULONG length;
	long index=0;
#ifdef _DEBUG
	DWORD dwTick = 0;
#endif
	
	if (bstrURL == NULL)
	{
		TRACE("CInternetFileManagerObject::GetFileComplex: incoming argument (BSTR) is NULL\n");
		return E_INVALIDARG;
	}

	if (pbstrFinalPath == NULL)	
	{
		TRACE("CInternetFileManagerObject::GetFileComplex: outgoing pointer (BSTR*) is NULL\n");
		return E_POINTER;
	}

	*pbstrFinalPath = NULL;

	//extract extension
	_splitpath(CString(bstrURL), NULL, NULL, NULL, szPath);
	strExtension = CString(szPath);
	strExtension = strExtension.Right(strExtension.GetLength()-1);

	strFullURL = bstrURL;

	//check if is fullurl.
	if (IsFullURL(bstrURL))
	{
#ifdef _DEBUG
		dwTick = GetTickCount();
#endif

		hr = URLDownloadToCacheFile(NULL, strFullURL, szPath, INTERNET_MAX_PATH_LENGTH, 0 /*BINDF_GETNEWESTVERSION*/, NULL);

		if (SUCCEEDED(hr))
		{
			strFilename = CString(szPath);
			
#ifdef _DEBUG
			TRACE("CInternetFileManagerObject::GetFileComplex: successfully downloaded %s as %s, duration %3.2f sec\n", strFullURL, strFilename, (float)(GetTickCount() - dwTick) / 1000.0);
#endif

			*pbstrFinalURL = strFullURL.AllocSysString();
			*pbstrFinalPath = strFilename.AllocSysString();
		}
		else
		{
#ifdef _DEBUG
//			TRACE("CInternetFileManagerObject::GetFileComplex: failed to download %s, hr %x, duration %3.2f sec\n", strFullURL, (float)(GetTickCount() - dwTick) / 1000.0);
#endif

			hr = INETFILE_E_FILENOTFOUND;
		}
	}
	else
	{
		if (m_RootURLs.GetSize() == 0)
		{
			TRACE("CInternetFileManagerObject::GetFileComplex: root URL list is empty\n");
			return INETFILE_E_INVALIDROOTURL;
		}

		//iterate through each url;
		for (index=0; index<m_RootURLs.GetSize(); index++)
		{
			hr = S_OK;

#ifdef _DEBUG
			dwTick = GetTickCount();
#endif

			strFullURL = m_RootURLs[index] + "/" + CString(bstrURL);
			
			//find a cache name.
			length = sizeof(cinfo);
			
			bRetVal = RetrieveUrlCacheEntryFile(strFullURL,(INTERNET_CACHE_ENTRY_INFO *)&cinfo, &length, 0);

			UnlockUrlCacheEntryFile(strFullURL, 0);

			if (!bRetVal) 
			{	
				hr = URLDownloadToCacheFile(NULL, strFullURL, szPath, INTERNET_MAX_PATH_LENGTH, 0 /*BINDF_GETNEWESTVERSION*/, NULL);
				if (SUCCEEDED(hr)) 
				{
					strFilename = CString(szPath);
				
#ifdef _DEBUG
					TRACE("CInternetFileManagerObject::GetFileComplex: successfully downloaded %s as %s, duration %3.2f sec\n", strFullURL, strFilename, (float)(GetTickCount() - dwTick) / 1000.0);
#endif
				}
				else
				{
#ifdef _DEBUG
//					TRACE("CInternetFileManagerObject::GetFileComplex: failed to download %s, duration %3.2f sec\n", strFullURL, (float)(GetTickCount() - dwTick) / 1000.0);
#endif

					UnlockUrlCacheEntryFile(strFullURL, 0);
					DeleteUrlCacheEntry(strFullURL);

					hr = INETFILE_E_FILENOTFOUND;

					continue;
				}
			}
			else
			{
				strFilename = CString(((INTERNET_CACHE_ENTRY_INFO *)&cinfo)->lpszLocalFileName);

#ifdef _DEBUG
				TRACE("CInternetFileManagerObject::GetFileComplex: using cached URL %s as %s, duration %3.2f sec\n", 
					strFullURL, strFilename, (float)(GetTickCount() - dwTick) / 1000.0);	
#endif
			}
			
			*pbstrFinalURL = strFullURL.AllocSysString();
			*pbstrFinalPath = strFilename.AllocSysString();

			break;
		}
	}
	
//	if(*pbstrFinalPath==NULL)
//		hr=E_FAIL;

	return hr;
}