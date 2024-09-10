int CMainFrameWork::InitSoUiFrame()
{
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

	int nRet = 0; 

	SComMgr * pComMgr = new SComMgr;
	//将程序的运行路径修改到项目所在目录所在的目录
	TCHAR szCurrentDir[MAX_PATH]={0};
	GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	_tcscpy(lpInsertPos+1,_T("\\..\\TestProject"));
	SetCurrentDirectory(szCurrentDir);

	{
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
		pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
		pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);

		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

		SApplication *theApp=new SApplication(pRenderFactory,g_hInstance);

		CAutoRefPtr<IResProvider>   pResProvider;
#if (RES_TYPE == 0)
		CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
		if(!pResProvider->Init((LPARAM)_T("uires"),0))
		{
			SASSERT(0);
			return 1;
		}
#else 
		CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
		pResProvider->Init((WPARAM)hInstance,0);
#endif

		theApp->AddResProvider(pResProvider);

		CAutoRefPtr<ITranslatorMgr> trans;
		pComMgr->CreateTranslator((IObjRef**)&trans);
		if(trans)
		{
			theApp->SetTranslator(trans);
			pugi::xml_document xmlLang;
			if(theApp->LoadXmlDocment(xmlLang,_T("lang_cn"),_T("translator")))
			{
				CAutoRefPtr<ITranslator> langCN;
				trans->CreateTranslator(&langCN);
				langCN->Load(&xmlLang.child(L"language"),1);//1=LD_XML
				trans->InstallTranslator(langCN);
			}
		}

		 theApp->RegisterWndFactory(TplSWindowFactory<SIPAddressCtrl>());//注册IP控件

		//加载系统资源
		HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
		if(hSysResource)
		{
			CAutoRefPtr<IResProvider> sysSesProvider;
			CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
			sysSesProvider->Init((WPARAM)hSysResource,0);
			theApp->LoadSystemNamedResource(sysSesProvider);
		}

		theApp->Init(_T("XML_INIT")); 

		// BLOCK: Run application
		{
			CMainDlg dlgMain;  
			dlgMain.Create(GetActiveWindow(),0,0,0,0);
			dlgMain.SendMessage(WM_INITDIALOG);
			dlgMain.CenterWindow(dlgMain.m_hWnd);
			dlgMain.ShowWindow(SW_SHOWNORMAL);
			nRet=theApp->Run(dlgMain.m_hWnd);
		}

		delete theApp;
	}

	delete pComMgr;
	OleUninitialize();
}