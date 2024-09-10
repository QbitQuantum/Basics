void LogConfigWindow::CreateGUIControls()
{
	// Verbosity
	wxArrayString wxLevels, wxLevelsUse;
	wxLevels.Add(_("Notice"));
	wxLevels.Add(_("Error"));
	wxLevels.Add(_("Warning"));
	wxLevels.Add(_("Info"));
	wxLevels.Add(_("Debug"));
	for (int i = 0; i < MAX_LOGLEVEL; ++i)
		wxLevelsUse.Add(wxLevels[i]);
	m_verbosity = new wxRadioBox(this, wxID_ANY, _("Verbosity"),
			wxDefaultPosition, wxDefaultSize, wxLevelsUse, 0, wxRA_SPECIFY_ROWS);
	m_verbosity->Bind(wxEVT_RADIOBOX, &LogConfigWindow::OnVerbosityChange, this);

	// Options
	m_writeFileCB = new wxCheckBox(this, wxID_ANY, _("Write to File"));
	m_writeFileCB->Bind(wxEVT_CHECKBOX, &LogConfigWindow::OnWriteFileChecked, this);
	m_writeConsoleCB = new wxCheckBox(this, wxID_ANY, _("Write to Console"));
	m_writeConsoleCB->Bind(wxEVT_CHECKBOX, &LogConfigWindow::OnWriteConsoleChecked, this);
	m_writeWindowCB = new wxCheckBox(this, wxID_ANY, _("Write to Window"));
	m_writeWindowCB->Bind(wxEVT_CHECKBOX, &LogConfigWindow::OnWriteWindowChecked, this);
	m_writeDebuggerCB = nullptr;
#ifdef _MSC_VER
	if (IsDebuggerPresent())
	{
		m_writeDebuggerCB = new wxCheckBox(this, wxID_ANY, _("Write to Debugger"));
		m_writeDebuggerCB->Bind(wxEVT_CHECKBOX, &LogConfigWindow::OnWriteDebuggerChecked, this);
	}
#endif

	wxButton *btn_toggle_all = new wxButton(this, wxID_ANY, _("Toggle All Log Types"),
			wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btn_toggle_all->Bind(wxEVT_BUTTON, &LogConfigWindow::OnToggleAll, this);
	m_checks = new wxCheckListBox(this, wxID_ANY);
	m_checks->Bind(wxEVT_CHECKLISTBOX, &LogConfigWindow::OnLogCheck, this);
	for (int i = 0; i < LogTypes::NUMBER_OF_LOGS; i++)
		m_checks->Append(StrToWxStr(m_LogManager->GetFullName((LogTypes::LOG_TYPE)i)));

	// Sizers
	wxStaticBoxSizer* sbOutputs = new wxStaticBoxSizer(wxVERTICAL, this, _("Logger Outputs"));
	sbOutputs->Add(m_writeFileCB, 0, wxDOWN, 1);
	sbOutputs->Add(m_writeConsoleCB, 0, wxDOWN, 1);
#ifdef _MSC_VER
	if (m_writeDebuggerCB)
	{
		sbOutputs->Add(m_writeWindowCB, 0, wxDOWN, 1);
		sbOutputs->Add(m_writeDebuggerCB, 0);
	}
	else
#endif
	{
		sbOutputs->Add(m_writeWindowCB, 0);
	}

	wxStaticBoxSizer* sbLogTypes = new wxStaticBoxSizer(wxVERTICAL, this, _("Log Types"));
	sbLogTypes->Add(m_checks, 1, wxEXPAND);

	wxBoxSizer *sMain = new wxBoxSizer(wxVERTICAL);
	sMain->Add(m_verbosity, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	sMain->Add(sbOutputs, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	sMain->Add(btn_toggle_all, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	sMain->Add(sbLogTypes, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

	SetSizer(sMain);
	Layout();
}