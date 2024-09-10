bool OpenGLApp::initAPI(){
	PixelFormat pf;
	initPixelFormat(pf);
	selectPixelFormat(pf);

	int bpp = pf.alphaBits > 0? 32 : 24;
	wa = (pf.accumBits > 0);

    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof (PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bpp,
		0, 0, 0, 0, 0, 0, 0, 0,
		pf.accumBits, pf.accumBits / 4, pf.accumBits / 4, pf.accumBits / 4, pf.accumBits / 4,
		pf.depthBits,
		pf.stencilBits,
		pf.alphaBits,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
    };


	WNDCLASS wincl;
	HINSTANCE hInst = (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE);

	wincl.hInstance = hInst;
	wincl.lpszClassName = "PFrmt";
	wincl.lpfnWndProc = PFWinProc;
	wincl.style = 0;
	wincl.hIcon = NULL;
	wincl.hCursor = NULL;
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = NULL;
	RegisterClass(&wincl);

	HWND hPFwnd = CreateWindow("PFrmt", "PFormat", WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 8, 8, HWND_DESKTOP, NULL, hInst, NULL);
	initEntryPoints(hPFwnd, pfd);
	SendMessage(hPFwnd, WM_CLOSE, 0, 0);

	hdc = GetDC(hwnd);

	int pixelFormat;
	float fAttribs[256];
	int iAttribs[256] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,

		WGL_RED_BITS_ARB,       pf.redBits,
		WGL_GREEN_BITS_ARB,     pf.greenBits,
		WGL_BLUE_BITS_ARB,      pf.blueBits,
		WGL_ALPHA_BITS_ARB,     pf.alphaBits,
		WGL_DEPTH_BITS_ARB,     pf.depthBits,
		WGL_STENCIL_BITS_ARB,   pf.stencilBits,
		WGL_ACCUM_BITS_ARB,     pf.accumBits,
	};

	while (true){
		int   *iAtt = iAttribs + 20;
		float *fAtt = fAttribs;

		if (WGL_ARB_multisample_supported && pf.fsaaLevel > 0){
			*iAtt++ = WGL_SAMPLE_BUFFERS_ARB;
			*iAtt++ = GL_TRUE;

			*iAtt++ = WGL_SAMPLES_ARB;
			*iAtt++ = pf.fsaaLevel;
		}

		*iAtt++ = 0;
		*fAtt++ = 0;

		unsigned int nMatchingPixelFormats;
		if (!WGL_ARB_pixel_format_supported || !wglChoosePixelFormatARB(hdc, iAttribs, fAttribs, 1, &pixelFormat, &nMatchingPixelFormats) || nMatchingPixelFormats == 0){
			if (pf.fsaaLevel > 0){
				pf.fsaaLevel -= 2;
			} else {
				pixelFormat = ChoosePixelFormat(hdc, &pfd);
				break;
			}
		} else break;
	}

    SetPixelFormat(hdc, pixelFormat, &pfd);

	hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);

	initExtensions(hdc);

	if (WGL_ARB_multisample_supported && pf.fsaaLevel > 0){
		glEnable(GL_MULTISAMPLE_ARB);
	}


	renderer = new OpenGLRenderer(hdc, hglrc);

	return true;
}