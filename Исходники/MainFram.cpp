CMainFram* CMainFram::createShow()
{
	CMainFram* cmf = new CMainFram();
	cmf->Create();
	//cmf->LoadFrame(IDF_MAINFRAME,WS_OVERLAPPEDWINDOW,NULL,NULL);
	cmf->ShowWindow(SW_SHOW);
	return cmf;
}