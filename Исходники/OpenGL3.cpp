bool FOpenGL3Context::Construct( FViewport* InOwner, uint32 Width, uint32 Height )
{
	guard;

	Owner = InOwner;
	Res.X = Width;
	Res.Y = Height;

#if defined (_WIN32)
	if ((GLWndProps.hDC = GetDC( Owner->GetWindowProps().WindowHandle )) == NULL)
	{
		Throw( L"OpenGL3 Error : GetDC() returned NULL", true );
		return false;
	}

	GLWndProps.PFD =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,0,0,0,0,0,0,0,
		32,
		0,0,0,0,0,0,0
	};

	GLWndProps.PixelFormat = ChoosePixelFormat( GLWndProps.hDC, &GLWndProps.PFD );
	SetPixelFormat( GLWndProps.hDC, GLWndProps.PixelFormat, &GLWndProps.PFD );

	if ((GLWndProps.hRC = wglCreateContext( GLWndProps.hDC )) == NULL)
	{
		Throw( L"OpenGL3 Error : wglCreateContext() returned NULL", true );
		return false;
	}
	wglMakeCurrent( GLWndProps.hDC, GLWndProps.hRC );

	OnSize( Width, Height );
#endif

	if (glewInit() != GLEW_OK)
	{
		Throw( L"glewInit() failed.", true );
	}
	if (!GLEW_VERSION_3_3)
	{
		Throw( L"Minimum version of OpenGL 3.3 is not supported", true );
	}

	Logf( LOG_ENGINE, L"OpenGL 3.x viewport constructed" );
	return true;

	unguard;
}