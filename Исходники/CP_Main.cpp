void CCP_MainApp::ShowCommandLineError(CString csTitle, CString csMessage)
{
	Log(StrF(_T("ShowCommandLineError %s - %s"), csTitle, csMessage));

	CToolTipEx *pErrorWnd = new CToolTipEx;
	pErrorWnd->Create(NULL);
	pErrorWnd->SetToolTipText(csTitle + "\n\n" + csMessage);

	CPoint pt;
	CRect rcScreen;
	GetMonitorRect(0, &rcScreen);
	pt = rcScreen.BottomRight();

	CRect cr = pErrorWnd->GetBoundsRect();

	pt.x -= max(cr.Width()+50, 150);
	pt.y -= max(cr.Height()+50, 150);

	pErrorWnd->Show(pt);
	
	Sleep(4000);

	pErrorWnd->DestroyWindow();
}