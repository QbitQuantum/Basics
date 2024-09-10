// Spout OpenGL initialization function
bool SpoutSenderPlugin::InitOpenGL()
{
	char windowtitle[512];

	// We only need an OpenGL context with no window
	m_hwnd = GetForegroundWindow(); // Any window will do - we don't render to it
	if(!m_hwnd) { printf("InitOpenGL error 1\n"); MessageBoxA(NULL, "Error 1\n", "InitOpenGL", MB_OK); return false; }
	m_hdc = GetDC(m_hwnd);
	if(!m_hdc) { printf("InitOpenGL error 2\n"); MessageBoxA(NULL, "Error 2\n", "InitOpenGL", MB_OK); return false; }
	GetWindowTextA(m_hwnd, windowtitle, 256); // debug

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24; // LJ DEBUG - was 16;
	pfd.cStencilBits = 8; // LJ DEBUG -added
	pfd.iLayerType = PFD_MAIN_PLANE;

	int iFormat = ChoosePixelFormat(m_hdc, &pfd);
	if(!iFormat) { printf("InitOpenGL error 3\n"); MessageBoxA(NULL, "Error 3\n", "InitOpenGL", MB_OK); return false; }

	if(!SetPixelFormat(m_hdc, iFormat, &pfd)) { printf("InitOpenGL error 4\n"); MessageBoxA(NULL, "Error 4\n", "InitOpenGL", MB_OK); return false; }

	m_hRC = wglCreateContext(m_hdc);
	if(!m_hRC) { printf("InitOpenGL error 5\n"); MessageBoxA(NULL, "Error 5\n", "InitOpenGL", MB_OK); return false; }

	wglMakeCurrent(m_hdc, m_hRC);
	if(wglGetCurrentContext() == NULL) { printf("InitOpenGL error 6\n"); MessageBoxA(NULL, "Error 6\n", "InitOpenGL", MB_OK); return false; }

	// Set up a shared context
	if(!m_hSharedRC) m_hSharedRC = wglCreateContext(m_hdc);
	if(!m_hSharedRC) { printf("InitOpenGL shared context not created\n"); }
	if(!wglShareLists(m_hSharedRC, m_hRC)) { printf("wglShareLists failed\n"); }

	// Drop through to return true
	/*
	SendMessageTimeoutA(m_hwnd, WM_GETTEXT, 256, (LPARAM)windowtitle, SMTO_ABORTIFHUNG, 128, NULL);
	printf("InitOpenGL : hwnd = %x (%s), hdc = %x, context = %x\n", m_hwnd, windowtitle, m_hdc, m_hRC);
	int nTotalAvailMemoryInKB = 0;
	int nCurAvailMemoryInKB = 0;
	// GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX 0x9048
	// GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX 0x9049
	glGetIntegerv(0x9048, &nTotalAvailMemoryInKB);
	glGetIntegerv(0x9049, &nCurAvailMemoryInKB);
	printf("Memory : Total [%i], Available [%i]\n", nTotalAvailMemoryInKB, nCurAvailMemoryInKB);
	*/

	return true;

}