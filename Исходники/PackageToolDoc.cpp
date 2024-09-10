void CPackageToolDoc::OnSetupservermode()
{
	// TODO: 在此添加命令处理程序代码
	m_lCurPatchMode = 0;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		CMenu* pMenu = pMainFrame->GetMenu();
		if(pMenu)
		{
			pMenu->CheckMenuItem(ID_SETUPSERVERMODE, MF_CHECKED);
			pMenu->CheckMenuItem(ID_SETUPCLIENTMODE, MF_UNCHECKED);
		}
	}
}