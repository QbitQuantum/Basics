RimeWithWeaselHandler::RimeWithWeaselHandler(weasel::UI *ui)
	: m_ui(ui)
	, m_active_session(0)
	, m_disabled(true)
	, _UpdateUICallback(NULL)
	, m_vista_greater(IsWindowsVistaOrGreater())
{
	_Setup();
}