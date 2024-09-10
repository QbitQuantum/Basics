void AppSetting::saveSetting()
{
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt(REGKEY_APP_NAME, REGKEY_SHOW_NAVIGATION, showNavigation? 1:0);

	pApp->WriteProfileInt(REGKEY_APP_NAME, REGKEY_DISPLAY_TEXT, bShowHelpText? 1:0);
	pApp->WriteProfileInt(REGKEY_APP_NAME, REGKEY_DISPLAY_AXIS, bShowAxis? 1:0);
	pApp->WriteProfileStringA(REGKEY_APP_NAME,REGKEY_OBJECT_PATH,objPath);
	pApp->WriteProfileStringA(REGKEY_APP_NAME,REGKEY_SIM_DATA_PATH,simulationDataPath);
}