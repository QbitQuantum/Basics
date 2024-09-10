//\brief
//	initialize the gl extension functions address.
static bool InitializeGlew()
{
	GLenum err;
	GLContext ctx;

	/* create OpenGL rendering context */
	InitContext(&ctx);
	if (GL_TRUE == CreateContext(&ctx))
	{
		std::cout << "Error: CreateContext failed" << std::endl;
		DestroyContext(&ctx);
		return false;
	}

	/* initialize GLEW */
	glewExperimental = GL_TRUE;
#ifdef GLEW_MX
	err = glewContextInit(glewGetContext());
#  ifdef _WIN32
	err = err || wglewContextInit(wglewGetContext());
#  elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
	err = err || glxewContextInit(glxewGetContext());
#  endif
#else
	err = glewInit();
#endif
	if (GLEW_OK != err)
	{
		std::cout << "Error [main]: glewInit failed: " << glewGetErrorString(err) << std::endl;
		DestroyContext(&ctx);
		return false;
	}

	DestroyContext(&ctx);
	return true;
}