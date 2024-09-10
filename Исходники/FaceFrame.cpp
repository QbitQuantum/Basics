FaceFrame::FaceFrame()
	: wxFrame(NULL, -1, _T("XFaceEd"), wxDefaultPosition, wxSize(1024, 768)), m_dictionaryDlg(0)
{
	wxFileSystem::AddHandler(new wxZipFSHandler);
	m_help.AddBook(wxFileName(_T("./help.zip")));
	
	wxImage::AddHandler(new wxPNGHandler());
    wxIcon icon;
	bool test = icon.LoadFile(_T("./res/XFaceLogo.ico"), wxBITMAP_TYPE_ICO );
	SetIcons(wxIconBundle(icon));
	// set the frame icon
//	SetIcon(icon);

	SetStatusBar(CreateStatusBar(2));

	createMenu();
	
    m_splitter = new Splitter(this);
	
	try{
		m_GLwnd = new FaceView(m_splitter);
		m_GLwnd->Refresh();
		Mediator::getInstance()->regFaceView(m_GLwnd);
	}
	catch(...)
	{
		wxMessageBox(_T("Unable to create OpenGL window, you might have a problem with your video card drivers!"), _T("Exception"));
		Close(true);
	}
	
	m_panel = new LeftPanel(m_splitter, 0, 0, 350, 768);
	m_panel->InitDialog();
    m_splitter->SplitVertically(m_panel, m_GLwnd, 350);
	//m_splitter->SetMinimumPaneSize(300);

	SetDropTarget(new DropFDPFileTarget);

	SetTitle(_T("XfaceEd - No file loaded!"));
}