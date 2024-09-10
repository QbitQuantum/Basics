bool CTimerControlApp::OnInit()
{
	SetVendorName(VENDOR_NAME);

	if (!wxApp::OnInit())
		return false;

	if (!m_nolog) {
		wxString logBaseName = LOG_BASE_NAME;
		if (!m_name.IsEmpty()) {
			logBaseName.Append(wxT("_"));
			logBaseName.Append(m_name);
		}

		if (m_logDir.IsEmpty())
			m_logDir = wxFileName::GetHomeDir();

		wxLog* log = new CLogger(m_logDir, logBaseName);
		wxLog::SetActiveTarget(log);
	} else {
		new wxLogNull;
	}

	m_config = new CTimerControlConfig(new wxConfig(APPLICATION_NAME), m_name);

	wxString frameName = APPLICATION_NAME + wxT(" - ");
	if (!m_name.IsEmpty()) {
		frameName.Append(m_name);
		frameName.Append(wxT(" - "));
	}
	frameName.Append(VERSION);

	if (!m_name.IsEmpty()) {
		wxString fileBase = SCHEDULE_BASE_NAME;
		fileBase.Append(wxT("_"));
		fileBase.Append(m_name);
		fileBase.Replace(wxT(" "), wxT("_"));

		wxFileName fileName(wxFileName::GetHomeDir(), fileBase, wxT("dat"));
		m_fileName = fileName.GetFullPath();
	} else {
		wxFileName fileName(wxFileName::GetHomeDir(), SCHEDULE_BASE_NAME, wxT("dat"));
		m_fileName = fileName.GetFullPath();
	}

	wxPoint position = wxDefaultPosition;

	int x, y;
	getPosition(x, y);
	if (x >= 0 && y >= 0)
		position = wxPoint(x, y);

	bool delay;
	getDelay(delay);

	m_frame = new CTimerControlFrame(frameName, position, delay);
	m_frame->Show();

	SetTopWindow(m_frame);

	wxLogInfo(wxT("Starting ") + APPLICATION_NAME + wxT(" - ") + VERSION);

	// Log the SVN revsion and the version of wxWidgets and the Operating System
	wxLogInfo(SVNREV);
	wxLogInfo(wxT("Using wxWidgets %d.%d.%d on %s"), wxMAJOR_VERSION, wxMINOR_VERSION, wxRELEASE_NUMBER, ::wxGetOsDescription().c_str());

	createThread();

	return wxApp::OnInit();
}