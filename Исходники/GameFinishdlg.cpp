int CGameFinishDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	TCHAR szName[MAX_PATH];
	wsprintf(szName,TEXT(".\\image\\result.bmp"));
	m_bk.SetLoadInfo(szName,TRUE);

	wsprintf(szName,".\\image\\win.bmp");
	m_Flag.SetLoadInfo(szName,false);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	//this->MapWindowPoints(this->GetParent(),&ClientRect);
	CGameImageHelper	help(&m_bk);
	this->MoveWindow(ClientRect.left,ClientRect.top,help.GetWidth(),help.GetHeight());
	HRGN hRgn=AFCBmpToRgn(help,RGB(255,0,255),RGB(1,0,1));
	if (hRgn!=NULL)
	{
		SetWindowPos(NULL,0,0,help.GetWidth(),help.GetHeight(),SWP_NOMOVE);
		SetWindowRgn(hRgn,TRUE);
	}

	return 0;
}