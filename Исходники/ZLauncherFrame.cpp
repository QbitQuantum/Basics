ZLauncherFrame::ZLauncherFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	wxImage::SetDefaultLoadFlags(wxImage::GetDefaultLoadFlags() & ~wxImage::Load_Verbose);

	this->SetSizeHints( wxSize( 500,300 ), wxDefaultSize );
	this->SetBackgroundColour( APPLICATION_BACKGROUND );
	
	// GridBagSizer for the whole frame
	wxGridBagSizer* gridBagSizerFrame;
	gridBagSizerFrame = new wxGridBagSizer( 0, 0 );
	gridBagSizerFrame->SetFlexibleDirection( wxBOTH );
	gridBagSizerFrame->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	gridBagSizerFrame->SetMinSize( wxSize( 800,600 ) ); 

	// GridBagSizer For the "Body"  (HTML Window, etc.)
	wxGridBagSizer* gridBagSizerBody;
	gridBagSizerBody = new wxGridBagSizer( 0, 0 );
	gridBagSizerBody->SetFlexibleDirection( wxBOTH );
	gridBagSizerBody->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	// HTML Viewer
	m_htmlWin = wxWebView::New(this, wxID_ANY, wxWebViewDefaultURLStr, wxDefaultPosition, wxDefaultSize, wxWebViewBackendDefault, wxSIMPLE_BORDER);
	m_htmlWin->SetMinSize( wxSize( 400,300 ) );
	gridBagSizerBody->Add( m_htmlWin, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	// GridBagSizer for the right side of the window
	wxGridBagSizer* gridBagSizerRight;
	gridBagSizerRight = new wxGridBagSizer( 0, 0 );
	gridBagSizerRight->SetFlexibleDirection( wxBOTH );
	gridBagSizerRight->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	// Add a spacer, for empty space, at the left side of the close button
	gridBagSizerRight->Add( 0, 0, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	// Close Button (Top Right)
	m_CloseButtonImg_Normal.LoadFile(GetResourcesDirectory() + CLOSE_BUTTON_NORMAL, wxBITMAP_TYPE_PNG);
	m_CloseButtonImg_Disabled.LoadFile(GetResourcesDirectory() + CLOSE_BUTTON_DISABLED, wxBITMAP_TYPE_PNG);
	m_CloseButtonImg_Pressed.LoadFile(GetResourcesDirectory() + CLOSE_BUTTON_PRESSED, wxBITMAP_TYPE_PNG);
	m_CloseButtonImg_Focus.LoadFile(GetResourcesDirectory() + CLOSE_BUTTON_FOCUS, wxBITMAP_TYPE_PNG);
	m_CloseButtonImg_Hover.LoadFile(GetResourcesDirectory() + CLOSE_BUTTON_HOVER, wxBITMAP_TYPE_PNG);
	m_btnClose = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxBU_EXACTFIT | wxBU_NOTEXT);
	m_btnClose->SetBitmap(m_CloseButtonImg_Normal);
	m_btnClose->SetBitmapDisabled(m_CloseButtonImg_Disabled);
	m_btnClose->SetBitmapPressed(m_CloseButtonImg_Pressed);
	m_btnClose->SetBitmapFocus(m_CloseButtonImg_Focus);
	m_btnClose->SetBitmapCurrent(m_CloseButtonImg_Hover);
	m_btnClose->SetBackgroundColour(APPLICATION_BACKGROUND);
	m_btnClose->Enable(true);

	gridBagSizerRight->Add( m_btnClose, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gridBagSizerRight->AddGrowableCol( 0 );
	gridBagSizerRight->AddGrowableRow( 0 );

	gridBagSizerBody->Add( gridBagSizerRight, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxEXPAND, 5 );
	gridBagSizerBody->AddGrowableCol( 1 );
	gridBagSizerBody->AddGrowableRow( 0 );
	
	gridBagSizerFrame->Add( gridBagSizerBody, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	// Footer Area (Progress Bar and Launch button)
	wxGridBagSizer* gridBagSizerFooter;
	gridBagSizerFooter = new wxGridBagSizer( 0, 0 );
	gridBagSizerFooter->SetFlexibleDirection( wxBOTH );
	gridBagSizerFooter->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	// Text for the Progress Bar
	m_txtProgress = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );
	m_txtProgress->SetForegroundColour( COMPONENT_TEXT_COLOR );
	m_txtProgress->SetBackgroundColour( APPLICATION_BACKGROUND );
	
	gridBagSizerFooter->Add( m_txtProgress, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_BOTTOM|wxEXPAND, 5 );

	// Progress Bar
	m_progress = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_progress->SetValue( 0 );
	m_progress->SetMinSize( wxSize( 500,25 ) );
	
	gridBagSizerFooter->Add( m_progress, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_TOP|wxALL|wxEXPAND, 5 );
	gridBagSizerFooter->AddGrowableCol( 0 );
	gridBagSizerFooter->AddGrowableRow( 0 );
	
	gridBagSizerFrame->Add( gridBagSizerFooter, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	// Launch Button
	m_LaunchButtonImg_Normal.LoadFile(GetResourcesDirectory() + LAUNCH_BUTTON_NORMAL, wxBITMAP_TYPE_PNG);
	m_LaunchButtonImg_Disabled.LoadFile(GetResourcesDirectory() + LAUNCH_BUTTON_DISABLED, wxBITMAP_TYPE_PNG);
	m_LaunchButtonImg_Pressed.LoadFile(GetResourcesDirectory() + LAUNCH_BUTTON_PRESSED, wxBITMAP_TYPE_PNG);
	m_LaunchButtonImg_Focus.LoadFile(GetResourcesDirectory() + LAUNCH_BUTTON_FOCUS, wxBITMAP_TYPE_PNG);
	m_LaunchButtonImg_Hover.LoadFile(GetResourcesDirectory() + LAUNCH_BUTTON_HOVER, wxBITMAP_TYPE_PNG);
	m_btnLaunch = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxBU_EXACTFIT | wxBU_NOTEXT);
	m_btnLaunch->SetBitmap(m_LaunchButtonImg_Normal);
	m_btnLaunch->SetBitmapDisabled(m_LaunchButtonImg_Disabled);
	m_btnLaunch->SetBitmapPressed(m_LaunchButtonImg_Pressed);
	m_btnLaunch->SetBitmapFocus(m_LaunchButtonImg_Focus);
	m_btnLaunch->SetBitmapCurrent(m_LaunchButtonImg_Hover);
	m_btnLaunch->SetBackgroundColour(APPLICATION_BACKGROUND);
	m_btnLaunch->Enable( false );

	gridBagSizerFrame->Add( m_btnLaunch, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_BOTTOM|wxALL, 5 );
	gridBagSizerFrame->AddGrowableCol( 0 );
	gridBagSizerFrame->AddGrowableRow( 0 );
	
	this->SetSizer( gridBagSizerFrame );
	this->Layout();

	this->Centre( wxBOTH );

	// Set background image, if any.
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	if (g_BackgroundImage != wxEmptyString)
		m_backgroundImg.LoadFile(g_BackgroundImage, wxBITMAP_TYPE_PNG);


	// Bind Message Events
	Bind(wxEVT_PAINT, &ZLauncherFrame::PaintEvent, this);

	Bind(wxEVT_COMMAND_UPDATE_PROGRESS_BAR, &ZLauncherFrame::OnProgressBarUpdate, this);
	Bind(wxEVT_COMMAND_UPDATE_PROGRESS_TEXT, &ZLauncherFrame::OnProgressTextUpdate, this);

	Bind(wxEVT_COMMAND_HTML_SET_CONTENT, &ZLauncherFrame::OnHTMLSetContent, this);
	Bind(wxEVT_COMMAND_HTML_LOAD_PAGE, &ZLauncherFrame::OnHTMLLoadPage, this);

	Bind(wxEVT_COMMAND_ENABLE_LAUNCH_BUTTON, &ZLauncherFrame::OnEnableLaunchButton, this);

	Bind(wxEVT_CLOSE_WINDOW, &ZLauncherFrame::OnClose, this);

	Bind(wxEVT_WEBVIEW_NAVIGATING, &ZLauncherFrame::OnClickLink, this);

	// Bind Button Events
	m_btnClose->Bind(wxEVT_BUTTON, &ZLauncherFrame::OnCloseButtonClicked, this);
	m_btnLaunch->Bind(wxEVT_BUTTON, &ZLauncherFrame::OnLaunchButtonClicked, this);

	// Read Header html data from external file
	if (wxFile::Exists(GetResourcesDirectory() + g_PatchHTMLHeaderFileName))
	{
		wxFile headerFile(GetResourcesDirectory() + g_PatchHTMLHeaderFileName, wxFile::OpenMode::read);
		headerFile.ReadAll(&PatchHTMLHeader);
	}
	else
	{
		wxMessageBox(wxString::Format("HTML Header file missing. Make sure it can be found in the following directory:\n %s", GetResourcesDirectory() + g_PatchHTMLHeaderFileName), "Missing file", wxOK| wxICON_EXCLAMATION);
	}
}