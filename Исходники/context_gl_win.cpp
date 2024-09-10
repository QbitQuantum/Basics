Error ContextGL_Win::initialize() {

	static	PIXELFORMATDESCRIPTOR pfd= {
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,// No Alpha Buffer
		0,// Shift Bit Ignored
		0,// No Accumulation Buffer
		0, 0, 0, 0,// Accumulation Bits Ignored
		24,// 24Bit Z-Buffer (Depth Buffer)
		0,// No Stencil Buffer
		0,// No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0,// Reserved
		0, 0, 0	// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd))) {
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ERR_CANT_CREATE;								// Return FALSE
	}

	if (!(pixel_format=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL,"Can't Find A Suitable pixel_format.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ERR_CANT_CREATE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,pixel_format,&pfd))		// Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL,"Can't Set The pixel_format.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ERR_CANT_CREATE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL,"Can't Create A Temporary GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ERR_CANT_CREATE;								// Return FALSE
	}

	wglMakeCurrent(hDC,hRC);

	if (opengl_3_context) {

		int attribs[] = {
			 WGL_CONTEXT_MAJOR_VERSION_ARB, 3,//we want a 3.3 context
			 WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			 //and it shall be forward compatible so that we can only use up to date functionality
			 WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB|_WGL_CONTEXT_DEBUG_BIT_ARB,
		0}; //zero indicates the end of the array

		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL; //pointer to the method
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");

		if(wglCreateContextAttribsARB == NULL) //OpenGL 3.0 is not supported
		{
			MessageBox(NULL,"Cannot get Proc Adress for CreateContextAttribs", "ERROR",MB_OK|MB_ICONEXCLAMATION);
			wglDeleteContext(hRC);
			return ERR_CANT_CREATE;
		}

		HGLRC new_hRC;
		if (!(new_hRC=wglCreateContextAttribsARB(hDC,0, attribs)))
		{
			wglDeleteContext(hRC);
			MessageBox(NULL,"Can't Create An OpenGL 3.3 Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return ERR_CANT_CREATE;								// Return false
		}
		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);
		hRC=new_hRC;

		if (!wglMakeCurrent(hDC,hRC)) 				// Try To Activate The Rendering Context
		{
			MessageBox(NULL,"Can't Activate The GL 3.3 Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return ERR_CANT_CREATE;							// Return FALSE
		}

		printf("Activated GL 3.3 context");
	}

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)  wglGetProcAddress ("wglSwapIntervalEXT");
//	glWrapperInit(wrapper_get_proc_address);

	return OK;
}