UninstallForm::UninstallForm(wxWindow* parent, UserCore::UserI* user) : wxFrame(parent, wxID_ANY, PRODUCT_NAME_CATW(L" UnInstaller"), wxDefaultPosition, wxSize( 500,330 ), wxCAPTION|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL )
{
	m_pUser = user;

	wxPanel* pTitlePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,57 ), wxTAB_TRAVERSAL );
	pTitlePanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	m_labTitle = new wxStaticText(pTitlePanel, wxID_ANY, Managers::GetString(L"#DUN_UNINSTALL_HEADER"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labTitleInfo = new wxStaticText(pTitlePanel, wxID_ANY, Managers::GetString(L"#DUN_UNINSTALL_SUBHEADER"), wxDefaultPosition, wxDefaultSize, 0 );

	m_imgLogo = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("IDI_HEADER"), wxBITMAP_TYPE_RESOURCE ), wxDefaultPosition, wxSize( 150,57 ), 0 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );

	m_butRepair = new wxButton( this, wxID_ANY, Managers::GetString(L"#DUN_REPAIR"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butUninstall = new wxButton( this, wxID_ANY, Managers::GetString(L"#DUN_UNINSTALL"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butCancel = new wxButton( this, wxID_ANY, Managers::GetString(L"#CANCEL"), wxDefaultPosition, wxDefaultSize, 0 );

	wxFont font = m_labTitle->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	m_labTitle->SetFont(font);

	m_pContent = new UDFSettingsPanel(this);

	m_bContentSizer = new wxBoxSizer( wxHORIZONTAL );
	m_bContentSizer->Add(m_pContent, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	bSizer1->Add( m_butRepair, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	bSizer1->Add( m_butUninstall, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	bSizer1->Add( m_butCancel, 0, wxALL, 5 );


	wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizer2->Add( 10, 0, 1, wxEXPAND, 5 );
	fgSizer2->Add( m_labTitle, 0, wxALL, 5 );
	fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	fgSizer2->Add( m_labTitleInfo, 0, wxLEFT, 15 );

	pTitlePanel->SetSizer( fgSizer2 );
	pTitlePanel->Layout();


	wxFlexGridSizer* fgSizer3 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizer3->Add( pTitlePanel, 1, wxEXPAND, 5 );
	fgSizer3->Add( m_imgLogo, 0, 0, 5 );


	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 5, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 2 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizer1->Add( fgSizer3, 1, wxEXPAND, 5 );
	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	fgSizer1->Add( m_bContentSizer, 1, wxEXPAND|wxLEFT|wxRIGHT, 10 );
	fgSizer1->Add( m_staticline1, 1, wxEXPAND, 5 );
	fgSizer1->Add( bSizer1, 1, wxEXPAND, 5 );
	
	SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );

	this->SetSizer( fgSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	SetIcon(wxIcon(wxICON(IDI_ICONNORMAL)));

	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &UninstallForm::onButtonClicked, this);
	m_bComplete = false;
}