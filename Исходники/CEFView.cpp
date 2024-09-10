void CCEFView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

    CefRefPtr<ClientHandler> client(new ClientHandler());
	m_clientHandler = client;

    CefWindowInfo info;
	RECT rect;
	GetClientRect(&rect);
	info.SetAsChild(GetSafeHwnd(), rect);

	CefBrowserSettings browserSettings;
  browserSettings.web_security_disabled = true;

	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	errno_t err;
	GetModuleFileNameA(NULL, path_buffer, sizeof(path_buffer));
	err = _splitpath_s(path_buffer, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
	if (err != 0)
	{
		//TODO: Add Error Handler
	}
	std::string s = dir;
	s += "html";
	err = _makepath_s(path_buffer, _MAX_PATH, drive, s.c_str(), "index", "html");
	if (err != 0)
	{
		//TODO: Add Error Handler
	}
	CefBrowser::CreateBrowser(info, static_cast<CefRefPtr<CefClient> >(client), path_buffer, browserSettings); 

	// TODO: Add your specialized code here and/or call the base class
}