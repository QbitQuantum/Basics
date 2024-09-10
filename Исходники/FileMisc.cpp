CString FileMisc::ResolveShortcut(LPCTSTR szShortcut)
{
	// start by checking its a valid file
	if (!FileExists(szShortcut))
	{
		return _T("");
	}

	CoInitialize(NULL);

	HRESULT hResult;
	IShellLink* psl;
	CString sTarget(szShortcut);

	hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);

	if (SUCCEEDED(hResult))
	{
		LPPERSISTFILE ppf;

		hResult = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

		if (SUCCEEDED(hResult))
		{
			hResult = ppf->Load(ATL::CT2OLE(szShortcut), STGM_READ);

			if (SUCCEEDED(hResult))
			{
				hResult = psl->Resolve(NULL, SLR_ANY_MATCH | SLR_NO_UI);

				if (SUCCEEDED(hResult))
				{
					TCHAR szPath[MAX_PATH];
					WIN32_FIND_DATA wfd;

					//fabio_2005
#if _MSC_VER >= 1400
					_tcscpy_s(szPath, szShortcut);
#else
					_tcscpy(szPath, szShortcut);
#endif
					hResult = psl->GetPath(szPath, MAX_PATH, (WIN32_FIND_DATA*)&wfd, SLGP_SHORTPATH);

					if (SUCCEEDED(hResult))
					{
						sTarget = CString(szPath);
					}
				}
			}

			ppf->Release();
		}

		psl->Release();
	}

	CoUninitialize();

	return sTarget;
}