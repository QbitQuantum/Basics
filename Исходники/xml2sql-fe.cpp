LRESULT MainDialog::OnInitDialog(HWND hwnd, LPARAM lp)
{
	WTL::CMessageLoop *loop = _Module.GetMessageLoop();
	loop->AddMessageFilter(this);
	
	DragAcceptFiles(*this, true);
	SetIcon(WTL::AtlLoadIconImage(IDI_MEDIAWIKI, 0,
		GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON)));
	SetIcon(WTL::AtlLoadIconImage(IDI_MEDIAWIKI, 0,
		GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON)), false);
	
	EnableDlgItem(IDC_OPT_COMPRESS_FULL, false);
	EnableDlgItem(IDC_START, false);
	
	DoDataExchange();
	m_progress.SetRange(0, 100);
	
	m_waitcursor.LoadOEMCursor(IDC_WAIT);
	
	return false;
}