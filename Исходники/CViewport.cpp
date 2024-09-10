//===========================================================================
bool cViewport::update(bool resizeOnly)
{

    // Clean up the old rendering context if necessary
    if ((resizeOnly == false) && m_glDC) cleanup();

    // declare variables
    int formatIndex;

    // viewport is not yet enabled
    m_enabled = false;

    // gl display not yet ready
    m_glReady = false;

    // check display handle
    if (m_winHandle == NULL) { return (false); }

    // Find out the rectangle to which we should be rendering

    // If we're using the entire window...
    if (m_forceRenderArea.left == -1)
    {
        if (GetWindowRect(m_winHandle, &m_activeRenderingArea) == 0) { return (false); }

        // Convert from screen to window coordinates
        m_activeRenderingArea.right -= m_activeRenderingArea.left;
        m_activeRenderingArea.left = 0;

        m_activeRenderingArea.bottom -= m_activeRenderingArea.top;
        m_activeRenderingArea.top = 0;

        // Convert from y-axis-down to y-axis-up, since that's how we store
        // our rendering area.
        int height = m_activeRenderingArea.bottom;
        m_activeRenderingArea.top = height - m_activeRenderingArea.top;
        m_activeRenderingArea.bottom = height - m_activeRenderingArea.bottom;
    }

    // Otherwise use whatever rectangle the user wants us to use...
    else
    {
        m_activeRenderingArea = m_forceRenderArea;
    }

    // retrieve handle of the display device context
    m_glDC = ::GetDC(m_winHandle);

    if (m_glDC == 0)
    {
       return(false);
    }

    if (resizeOnly == false)
    {
        // find pixel format supported by the device context. If error return false.
        formatIndex = ChoosePixelFormat(m_glDC, &m_pixelFormat);
        if (formatIndex == 0)
        {
            return(false);
        }

        // sets the specified device context's pixel format. If error return false
        if (!SetPixelFormat(m_glDC, formatIndex, &m_pixelFormat))
        {
            return(false);
        }

        formatIndex = GetPixelFormat (m_glDC);
        DescribePixelFormat (m_glDC, formatIndex, sizeof(PIXELFORMATDESCRIPTOR), &m_pixelFormat);

        // if stereo was enabled but can not be displayed, switch over to mono.
        if (((m_pixelFormat.dwFlags & PFD_STEREO) == 0) && m_stereoEnabled)
        {
            m_stereoEnabled = false;
        }

        // create display context
        m_glContext = wglCreateContext(m_glDC);
        if (m_glContext == 0)
        {
            return(false);
        }

        wglMakeCurrent(m_glDC, m_glContext);
    }

    // OpenGL is now ready for rendering
    m_glReady = true;

    // store this current view as the last active one
    lastActiveViewport = this;

    // enable viewport
    m_enabled = true;

    if (resizeOnly == false) onDisplayReset();

    // return success
    return(true);
}