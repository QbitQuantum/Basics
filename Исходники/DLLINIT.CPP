BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
#ifdef _AFX_OLE_IMPL
		BOOL bRegister = !coreDLL.bInitialized;

		// shared initialization
		AFX_MODULE_STATE* pModuleState = _AfxGetOleModuleState();
		pModuleState->m_hCurrentInstanceHandle = hInstance;
		pModuleState->m_hCurrentResourceHandle = hInstance;
		pModuleState->m_pClassInit = pModuleState->m_classList.GetHead();
		pModuleState->m_pFactoryInit = pModuleState->m_factoryList.GetHead();
#endif

		// initialize this DLL's extension module
		VERIFY(AfxInitExtensionModule(coreDLL, hInstance));

#ifdef _AFX_OLE_IMPL
		AfxWinInit(hInstance, NULL, &afxChNil, 0);

		// Register class factories in context of private module state
		if (bRegister)
			COleObjectFactory::RegisterAll();
#endif

#ifdef _AFX_OLE_IMPL
		// restore previously-saved module state
		VERIFY(AfxSetModuleState(AfxGetThreadState()->m_pPrevModuleState) ==
			_AfxGetOleModuleState());
		DEBUG_ONLY(AfxGetThreadState()->m_pPrevModuleState = NULL);
#endif

		// wire up this DLL into the resource chain
		CDynLinkLibrary* pDLL = new CDynLinkLibrary(coreDLL, TRUE);
		ASSERT(pDLL != NULL);
		pDLL->m_factoryList.m_pHead = NULL;

		// load language specific DLL
		// the DLL must be in the "system directory"
		static const char szPrefix[] = "\\MFC42";
		static const char szLOC[] = "LOC";
		static const char szDLL[] = ".DLL";
		char szLangDLL[_MAX_PATH+14]; // Note: 8.3 name
		GetSystemDirectoryA(szLangDLL, _countof(szLangDLL));
		lstrcatA(szLangDLL, szPrefix);

		// try MFC42LOC.DLL
		lstrcatA(szLangDLL, szLOC);
		lstrcatA(szLangDLL, szDLL);
		HINSTANCE hLangDLL = LoadLibraryA(szLangDLL);
		AFX_MODULE_STATE* pState = AfxGetModuleState();
		pState->m_appLangDLL = hLangDLL;

#ifdef _AFX_OLE_IMPL
		// copy it to the private OLE state too
		pModuleState->m_appLangDLL = hLangDLL;
#endif
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// free language specific DLL
		AFX_MODULE_STATE* pState = AfxGetModuleState();
		if (pState->m_appLangDLL != NULL)
		{
			::FreeLibrary(pState->m_appLangDLL);
			pState->m_appLangDLL = NULL;
		}

		// free the DLL info blocks
		CDynLinkLibrary* pDLL;
		while ((pDLL = pState->m_libraryList) != NULL)
			delete pDLL;
		ASSERT(pState->m_libraryList.IsEmpty());

		// cleanup module state for this process
		AfxTermExtensionModule(coreDLL);

#ifdef _AFX_OLE_IMPL
		// set module state for cleanup
		ASSERT(AfxGetThreadState()->m_pPrevModuleState == NULL);
		AfxGetThreadState()->m_pPrevModuleState =
			AfxSetModuleState(_AfxGetOleModuleState());
#endif

		// cleanup module state in OLE private module state
		AfxTermExtensionModule(coreDLL, TRUE);

		// free any local data for this process/thread
		AfxTermLocalData(NULL, TRUE);
	}
	else if (dwReason == DLL_THREAD_DETACH)
	{
		AfxTermThread();
	}

	return TRUE;    // ok
}