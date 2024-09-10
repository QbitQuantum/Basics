//------------------------------------------------------------------------------
GLContextImpl::GLContextImpl(GLContext & context, GLContextSettings & settings, GLContextImpl * sharedContext) :
	r_context(context),
    m_hrc(nullptr),
    m_dc(nullptr),
    m_ownHwnd(nullptr)
{
    // Get the HWND from either the passed window or an internal one
    HWND hwnd = nullptr;
	const Window * win = r_context.getWindow();
    if (win)
    {
        // A window was given, go with it
    	hwnd = (HWND)win->getHandle();
    }
    else
    {
        // No window was given...
        // On Windows, we still have to create a dummy window to get a valid DC
        m_ownHwnd = ::CreateWindow("STATIC", "", WS_POPUP | WS_DISABLED, 0, 0, 1, 1, NULL, NULL, GetModuleHandle(NULL), NULL);
        ShowWindow(m_ownHwnd, SW_HIDE);
        hwnd = m_ownHwnd;
    }

	m_dc = GetDC(hwnd);

	if (m_dc)
	{
        GLContextSettings initialSettings = settings;
		createContext(sharedContext ? sharedContext->m_hrc : nullptr, settings, hwnd);
		if (settings != initialSettings)
		{
			SN_WARNING("ContextSettings have been changed for compatibility.");
			SN_LOG("Requested: " << r_context.getSettings().toString());
			SN_LOG("Changed to: " << settings.toString());
		}
	}
}