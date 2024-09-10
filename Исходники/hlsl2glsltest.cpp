static bool InitializeOpenGL ()
{
	#if !USE_REAL_OPENGL_TO_CHECK
	return false;
	#endif
	
	bool hasGLSL = false;

#ifdef _MSC_VER
	// setup minimal required GL
	HWND wnd = CreateWindowA(
		"STATIC",
		"GL",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
		0, 0, 16, 16,
		NULL, NULL,
		GetModuleHandle(NULL), NULL );
	HDC dc = GetDC( wnd );

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA, 32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		16, 0,
		0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	int fmt = ChoosePixelFormat( dc, &pfd );
	SetPixelFormat( dc, fmt, &pfd );

	HGLRC rc = wglCreateContext( dc );
	wglMakeCurrent( dc, rc );

#elif defined(__APPLE__)
	CGLPixelFormatAttribute attributes[] = {
		kCGLPFAAccelerated,   // no software rendering
		(CGLPixelFormatAttribute) 0
	};
	CGLPixelFormatAttribute attributes3[] = {
		kCGLPFAAccelerated,   // no software rendering
		kCGLPFAOpenGLProfile, // core profile with the version stated below
		(CGLPixelFormatAttribute) kCGLOGLPVersion_3_2_Core,
		(CGLPixelFormatAttribute) 0
	};
	GLint num;
	CGLPixelFormatObj pix;
	
	// create legacy context
	CGLChoosePixelFormat(attributes, &pix, &num);
	if (pix == NULL)
		return false;
	CGLCreateContext(pix, NULL, &s_GLContext);
	if (s_GLContext == NULL)
		return false;
	CGLDestroyPixelFormat(pix);
	CGLSetCurrentContext(s_GLContext);
	
	// create core 3.2 context
	CGLChoosePixelFormat(attributes3, &pix, &num);
	if (pix == NULL)
		return false;
	CGLCreateContext(pix, NULL, &s_GLContext3);
	if (s_GLContext3 == NULL)
		return false;
	CGLDestroyPixelFormat(pix);
	
#else
        int argc = 0;
        char** argv = NULL;
        glutInit(&argc, argv);
        glutCreateWindow("hlsl2glsltest");
        glewInit();
#endif
	
	// check if we have GLSL
	const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
	hasGLSL = extensions != NULL && strstr(extensions, "GL_ARB_shader_objects") && strstr(extensions, "GL_ARB_vertex_shader") && strstr(extensions, "GL_ARB_fragment_shader");
	
	#if defined(__APPLE__)
	// using core profile; always has GLSL
	hasGLSL = true;
	#endif
	
	
#ifdef _MSC_VER
	if (hasGLSL)
	{
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	}
#endif
	

	return hasGLSL;
}