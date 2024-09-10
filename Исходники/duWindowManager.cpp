//////////////////////////////////////////////////////////////////////////
// Constructor/Distructor
duWindowManager::duWindowManager() :
	 m_pDocXml(NULL)
	,m_pResManager(NULL)
	,m_fZip(FALSE)
	,m_hZip(NULL)
	,m_pTrialImage(NULL)
	
{
	ZeroMemory(m_szSkinPath, MAX_PATH * sizeof(TCHAR));
	m_mapCtrlManager.clear();

	g_hInstance = GetInstanceModule(NULL);

	g_pTypeLib = new duTypeLib;
	g_pTypeLib->InitTypeInfo((HMODULE)g_hInstance);

	InitCommonControls();
	g_setValid = new set<duPlugin *>;
	g_setValid->clear();
	GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL); 

}