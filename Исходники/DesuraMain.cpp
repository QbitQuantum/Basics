BootLoader::BootLoader()
{
	signal(SIGABRT, CustomSigAbort);
	_set_error_mode(_OUT_TO_MSGBOX);

	m_MDumpHandle.showMessageBox(true);
	
	//AfxEnableMemoryTracking(FALSE);
	InitCommonControls();

	m_bHasAdminRights = false;
	m_pUICore = nullptr;
	m_bRetCode = false;
}