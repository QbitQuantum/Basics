bool XlLibraryInitialize(XlAddInExportInfo* pExportInfo)
{
	HRESULT hr;
	CComPtr<ICorRuntimeHost> pHost;

	hr = LoadClr20(&pHost);
	if (FAILED(hr) || pHost == NULL)
	{
		// LoadClr20 shows diagnostic MessageBoxes if needed.
		// Perhaps remember that we are not loaded?
		return 0;
	}

	// If all is fine now, also start the CLR (always safe to do again.
	hr = pHost->Start();
	if (FAILED(hr))
	{
		ShowMessage(IDS_MSG_HEADER_NEEDCLR20, 
					IDS_MSG_BODY_HOSTSTART,
					IDS_MSG_FOOTER_UNEXPECTED,
					hr);
		return 0;
	}

	CString addInFullPath = AddInFullPath();

	CPath xllDirectory(addInFullPath);
	xllDirectory.RemoveFileSpec();

	CComPtr<IUnknown> pAppDomainSetupUnk;
	hr = pHost->CreateDomainSetup(&pAppDomainSetupUnk);
	if (FAILED(hr) || pAppDomainSetupUnk == NULL)
	{
		ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
					IDS_MSG_BODY_APPDOMAINSETUP, 
					IDS_MSG_FOOTER_UNEXPECTED,
					hr);
		return 0;
	}

	CComQIPtr<IAppDomainSetup> pAppDomainSetup = pAppDomainSetupUnk;

	hr = pAppDomainSetup->put_ApplicationBase(CComBSTR(xllDirectory));
	if (FAILED(hr))
	{
		ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
					IDS_MSG_BODY_APPLICATIONBASE, 
					IDS_MSG_FOOTER_UNEXPECTED,
					hr);
		return 0;
	}
	
	CComBSTR configFileName = addInFullPath;
	configFileName.Append(L".config");
	pAppDomainSetup->put_ConfigurationFile(configFileName);

	CComBSTR appDomainName = L"ExcelDna: ";
	appDomainName.Append(addInFullPath);
	pAppDomainSetup->put_ApplicationName(appDomainName);

	IUnknown *pAppDomainUnk = NULL;
	hr = pHost->CreateDomainEx(appDomainName, pAppDomainSetupUnk, 0, &pAppDomainUnk);
	if (FAILED(hr) || pAppDomainUnk == NULL)
	{
		ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
					IDS_MSG_BODY_APPDOMAIN, 
					IDS_MSG_FOOTER_UNEXPECTED,
					hr);
		return 0;
	}

	CComQIPtr<_AppDomain> pAppDomain(pAppDomainUnk);

	// Load plan for ExcelDna.Loader:
	// Try AppDomain.Load with the name ExcelDna.Loader.
	// Then if it does not work, we will try to load from a known resource in the .xll.

	CComPtr<_Assembly> pExcelDnaLoaderAssembly;
	hr = pAppDomain->Load_2(CComBSTR(L"ExcelDna.Loader"), &pExcelDnaLoaderAssembly);
	if (FAILED(hr) || pExcelDnaLoaderAssembly == NULL)
	{
		HRSRC hResInfoLoader = FindResource(hModuleCurrent, L"EXCELDNA_LOADER", L"ASSEMBLY");
		if (hResInfoLoader == NULL)
		{
			ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
						IDS_MSG_BODY_MISSINGEXCELDNALOADER, 
						IDS_MSG_FOOTER_UNEXPECTED,
						hr);
			return 0;
		}
		HGLOBAL hLoader = LoadResource(hModuleCurrent, hResInfoLoader);
		void* pLoader = LockResource(hLoader);
		ULONG sizeLoader = (ULONG)SizeofResource(hModuleCurrent, hResInfoLoader);
		
		CComSafeArray<BYTE> bytesLoader;
		bytesLoader.Add(sizeLoader, (byte*)pLoader);

		hr = pAppDomain->Load_3(bytesLoader, &pExcelDnaLoaderAssembly);
		if (FAILED(hr))
		{
			ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
						IDS_MSG_BODY_EXCELDNALOADER, 
						IDS_MSG_FOOTER_UNEXPECTED,
						hr);
			return 0;
		}

		CComBSTR pFullName;
		hr = pExcelDnaLoaderAssembly->get_FullName(&pFullName);
		if (FAILED(hr))
		{
			ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
						IDS_MSG_BODY_EXCELDNALOADERNAME, 
						IDS_MSG_FOOTER_UNEXPECTED,
						hr);
			return 0;
		}
	}
	
	CComPtr<_Type> pXlAddInType;
	hr = pExcelDnaLoaderAssembly->GetType_2(CComBSTR(L"ExcelDna.Loader.XlAddIn"), &pXlAddInType);
	if (FAILED(hr) || pXlAddInType == NULL)
	{
		ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
					IDS_MSG_BODY_XLADDIN, 
					IDS_MSG_FOOTER_UNEXPECTED,
					hr);
		return 0;
	}

	CComSafeArray<VARIANT> initArgs;
	initArgs.Add(CComVariant((INT32)pExportInfo));
	initArgs.Add(CComVariant((INT32)hModuleCurrent));
	initArgs.Add(CComVariant(addInFullPath.AllocSysString()));
	CComVariant initRetVal;
	CComVariant target;
	hr = pXlAddInType->InvokeMember_3(CComBSTR("Initialize"), (BindingFlags)(BindingFlags_Static | BindingFlags_Public | BindingFlags_InvokeMethod), NULL, target, initArgs, &initRetVal);
	if (FAILED(hr))
	{
		ShowMessage(IDS_MSG_HEADER_APPDOMAIN, 
					IDS_MSG_BODY_XLADDININIT, 
					IDS_MSG_FOOTER_UNEXPECTED,
					hr);
		return 0;
	}

	pHost_ForUnload = pHost.Detach();
	pAppDomain_ForUnload = (IUnknown*)pAppDomain.Detach();

	return initRetVal.boolVal == 0 ? false : true;
}