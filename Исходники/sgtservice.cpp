int CGtserviceModule::Run(int nShowCmd )
{
	CMessageLoop theLoop;
	AddMessageLoop(&theLoop);

	CMainDlg dlgMain;
	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}
	m_pdlgMain = &dlgMain;
	dlgMain.ShowWindow(nShowCmd);

	
	StartWork();
	
	int nRet = theLoop.Run();
	_Module.RemoveMessageLoop();
	return nRet;
}