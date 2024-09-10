ClientHandler::ClientHandler()
	: 
	  m_bFocusOnEditableField(false)
{
	sClientApp->addClientHandler(CefRefPtr<ClientHandler>(this));

	//ofLogNotice() << (__FUNCTION__) << std::endl;

	CreateProcessMessageDelegates(process_message_delegates_);

	// Read command line settings.
	CefRefPtr<CefCommandLine> command_line =
	    CefCommandLine::GetGlobalCommandLine();

	if (command_line->HasSwitch(cefclient::kUrl))
		m_StartupURL = command_line->GetSwitchValue(cefclient::kUrl);
	if (m_StartupURL.empty())
		m_StartupURL = "http://www.google.com/";

	// Also use external dev tools if off-screen rendering is enabled since we
	// disallow popup windows.
	m_bExternalDevTools = true;

	m_bMouseCursorChangeDisabled =
	    command_line->HasSwitch(cefclient::kMouseCursorChangeDisabled);

	//  Grab the openframeworks Window Handle
	ofxWindowHandle = WindowFromDC(wglGetCurrentDC());

}