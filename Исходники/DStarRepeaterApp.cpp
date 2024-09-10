bool CDStarRepeaterApp::OnInit()
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

#if defined(__WINDOWS__)
		if (m_logDir.IsEmpty())
			m_logDir = ::wxGetHomeDir();
#else
		if (m_logDir.IsEmpty())
			m_logDir = wxT(LOG_DIR);
#endif

		wxLog* log = new CLogger(m_logDir, logBaseName);
		wxLog::SetActiveTarget(log);
	} else {
		new wxLogNull;
	}

	m_logChain = new wxLogChain(new CDStarRepeaterLogger);

	wxString appName;
	if (!m_name.IsEmpty())
		appName = APPLICATION_NAME + wxT(" ") + m_name;
	else
		appName = APPLICATION_NAME;

#if !defined(__WINDOWS__)
	appName.Replace(wxT(" "), wxT("_"));
	m_checker = new wxSingleInstanceChecker(appName, wxT("/tmp"));
#else
	m_checker = new wxSingleInstanceChecker(appName);
#endif

	bool ret = m_checker->IsAnotherRunning();
	if (ret) {
		wxLogError(wxT("Another copy of the D-Star Repeater is running, exiting"));
		return false;
	}

#if defined(__WINDOWS__)
	if (m_confDir.IsEmpty())
		m_confDir = ::wxGetHomeDir();

	m_config = new CDStarRepeaterConfig(new wxConfig(APPLICATION_NAME), m_confDir, CONFIG_FILE_NAME, m_name);
#else
	if (m_confDir.IsEmpty())
		m_confDir = wxT(CONF_DIR);

	m_config = new CDStarRepeaterConfig(m_confDir, CONFIG_FILE_NAME, m_name);
#endif

	wxString type;
	m_config->getModem(type);

	wxString frameName = APPLICATION_NAME + wxT(" (") + type + wxT(") - ");
	if (!m_name.IsEmpty()) {
		frameName.Append(m_name);
		frameName.Append(wxT(" - "));
	}
	frameName.Append(VERSION);

	wxPoint position = wxDefaultPosition;

	int x, y;
	m_config->getPosition(x, y);
	if (x >= 0 && y >= 0)
		position = wxPoint(x, y);

	m_frame = new CDStarRepeaterFrame(frameName, type, position, m_gui);
	m_frame->Show();

	SetTopWindow(m_frame);

	wxLogInfo(wxT("Starting ") + APPLICATION_NAME + wxT(" - ") + VERSION);

	// Log the version of wxWidgets and the Operating System
	wxLogInfo(wxT("Using wxWidgets %d.%d.%d on %s"), wxMAJOR_VERSION, wxMINOR_VERSION, wxRELEASE_NUMBER, ::wxGetOsDescription().c_str());

	createThread();

	return true;
}