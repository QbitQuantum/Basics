BOOL CDlgScraperOutput::DestroyWindow()
{
	WINDOWPLACEMENT		wp;
	CMainFrame			*pMyMainWnd  = (CMainFrame *) (theApp.m_pMainWnd);

	// Save settings to registry
	GetWindowPlacement(&wp);
	prefs.set_scraper_x(wp.rcNormalPosition.left);
	prefs.set_scraper_y(wp.rcNormalPosition.top);
	prefs.set_scraper_dx(wp.rcNormalPosition.right - wp.rcNormalPosition.left);
	prefs.set_scraper_dy(wp.rcNormalPosition.bottom - wp.rcNormalPosition.top);
	prefs.set_scraper_zoom(m_Zoom.GetCurSel());

	// Uncheck scraper output button on main toolbar
	pMyMainWnd->m_MainToolBar.GetToolBarCtrl().CheckButton(ID_MAIN_TOOLBAR_SCRAPER_OUTPUT, false);

	return CDialog::DestroyWindow();
}