void WGLRenderer::init(Device *device, Renderer *other) {
	WGLDevice *wglDevice = static_cast<WGLDevice *>(device);

	if (m_session == NULL) {
		Log(EDebug, "Using an existing WGL context");
		m_context = wglGetCurrentContext();
		if (m_context == NULL)
			Log(EError, "Unable to retrieve the current WGL context!");
		m_borrowed = true;
	} else {
		/* Create a GL context */
		Log(EDebug, "Initializing WGL renderer");
		m_context = wglCreateContext(wglDevice->getDeviceContext());

		if (other != NULL) {
			Assert(other->getClass() == m_theClass);
			if (wglShareLists(m_context,
				static_cast<WGLRenderer *>(other)->m_context) != TRUE)
				Log(EError, "Unable to set up context sharing: %s",
					lastErrorText().c_str());
		}

		device->makeCurrent(this);
		m_borrowed = false;
	}

	GLRenderer::init(device);

	m_initialized = true;
}