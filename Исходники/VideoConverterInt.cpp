HRESULT __stdcall vcInitialize()
{
	GetTempPath(MAX_PATH, g_szTempPath);
	PathRemoveBackslash(g_szTempPath);
	GetModuleFileName(NULL, g_szModulePath, MAX_PATH);
	PathRemoveFileSpec(g_szModulePath);

	CreateLogFile(); 
	GetOSDisplayString(); 
	GetSystemInformations(); 
	InitGdiplus();
	InitCommonResource(); 
	InitHSBControlWindow();
	ffmpeg_init(); 
	LoadProfiles();
	InitMediaMananger(); 
	InitVideoPlayer();
	InitVideoRender();
	
	StringCchCopy(g_merge_info.m_Name, 256, L"merged");

	if (LoadOptions() != S_OK)
	{
		SHGetFolderPath(NULL, CSIDL_MYVIDEO | CSIDL_FLAG_CREATE, NULL, 0, g_opt.m_OutputPath);
		g_opt.m_Parallel = g_cpu_count;
		g_opt.m_FillColor2 = 0xFFFFFFFF;
	}

	if (LoadProfileSettings() != S_OK)
	{
		ZeroMemory(&g_ProfileSettings, sizeof(g_ProfileSettings));
		GetDefaultProfileSetting1(g_ProfileSettings, GROUP_VIDEO);
	}
	CopyProfileSettings();
	
	return S_OK;
}