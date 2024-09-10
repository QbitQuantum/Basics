/*
** OS Specific windowing context creation - essential for creating the OpenGL drawing context
*/
AESDK_OpenGL_Err AESDK_OpenGL_Startup(AESDK_OpenGL_EffectCommonData& inData)
{
	AESDK_OpenGL_Err result = AESDK_OpenGL_OK;
	inData.mUsingShaderB = false; //default value
	try
	{
#ifdef AE_OS_WIN
		WNDCLASSEX winClass; 
		MSG        uMsg;

		::memset(&uMsg,0,sizeof(uMsg));

		winClass.lpszClassName = "AESDK_OpenGL_Win_Class";
		winClass.cbSize        = sizeof(WNDCLASSEX);
		winClass.style         = CS_HREDRAW | CS_VREDRAW;
		winClass.lpfnWndProc   = ::DefWindowProc;
		winClass.hInstance     = NULL;
		winClass.hIcon	       = NULL;
		winClass.hIconSm	   = NULL;
		winClass.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
		winClass.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
		winClass.lpszMenuName  = NULL;
		winClass.cbClsExtra    = 0;
		winClass.cbWndExtra    = 0;
		
		if( !(::RegisterClassEx(&winClass)) )
			GL_CHECK(AESDK_OpenGL_OS_Load_Err);

		inData.mHWnd = ::CreateWindowEx( NULL, "AESDK_OpenGL_Win_Class", 
								 "OpenGL-using FBOs in AE",
									0,0, 
									0, 50, 50,
									NULL, 
									NULL, 
									NULL,
									NULL	);

		if( inData.mHWnd == NULL )
			GL_CHECK(AESDK_OpenGL_OS_Load_Err);
		
		GLuint PixelFormat;
		PIXELFORMATDESCRIPTOR pfd;
		::ZeroMemory( &pfd, sizeof( pfd ) );

		pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion   = 1;
		pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 8;
		
		
		inData.mHDC = ::GetDC( inData.mHWnd );
		PixelFormat = ChoosePixelFormat( inData.mHDC, &pfd );
		SetPixelFormat( inData.mHDC, PixelFormat, &pfd);
		
		inData.mHRC = wglCreateContext( inData.mHDC );
		wglMakeCurrent( inData.mHDC, inData.mHRC );

		//check for the appropriate extensions -  EXT_framebuffer_object
		char *ext = (char*)glGetString( GL_EXTENSIONS );
		if( ::strstr( ext, "EXT_framebuffer_object" ) == NULL )
		{		
			GL_CHECK(AESDK_OpenGL_Extensions_Err);
		}
		else
		{
			glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC)GetProcAddress("glIsRenderbufferEXT");
			glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)GetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)GetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)GetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)GetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)GetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC)GetProcAddress("glIsFramebufferEXT");
			glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)GetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)GetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)GetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)GetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)GetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)GetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)GetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)GetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)GetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)GetProcAddress("glGenerateMipmapEXT");
			glActiveTexture = (PFNGLACTIVETEXTUREPROC)GetProcAddress("glActiveTexture");

			if( !glIsRenderbufferEXT || !glBindRenderbufferEXT || !glDeleteRenderbuffersEXT || 
				!glGenRenderbuffersEXT || !glRenderbufferStorageEXT || !glGetRenderbufferParameterivEXT || 
				!glIsFramebufferEXT || !glBindFramebufferEXT || !glDeleteFramebuffersEXT || 
				!glGenFramebuffersEXT || !glCheckFramebufferStatusEXT || !glFramebufferTexture1DEXT || 
				!glFramebufferTexture2DEXT || !glFramebufferTexture3DEXT || !glFramebufferRenderbufferEXT||  
				!glGetFramebufferAttachmentParameterivEXT || !glGenerateMipmapEXT || !glActiveTexture)
			{
				GL_CHECK(AESDK_OpenGL_Extensions_Err);
			}
			
		}
		
		char *extP = (char*)glGetString( GL_EXTENSIONS );
		if( ::strstr( extP, "GL_ARB_shading_language_100" ) == NULL )
		{
			//This extension string indicates that the OpenGL Shading Language,
			// version 1.00, is supported.
			GL_CHECK(AESDK_OpenGL_ShaderInit_Err);
		}
	
		//check for the appropriate extensions -  EXT_framebuffer_object
		if( ::strstr( extP, "GL_ARB_shader_objects" ) == NULL )
		{		
			GL_CHECK(AESDK_OpenGL_Extensions_Err);
		}
		else
		{
			glCreateProgramObjectARB  = (PFNGLCREATEPROGRAMOBJECTARBPROC)GetProcAddress("glCreateProgramObjectARB");
			glDeleteObjectARB         = (PFNGLDELETEOBJECTARBPROC)GetProcAddress("glDeleteObjectARB");
			glUseProgramObjectARB     = (PFNGLUSEPROGRAMOBJECTARBPROC)GetProcAddress("glUseProgramObjectARB");
			glCreateShaderObjectARB   = (PFNGLCREATESHADEROBJECTARBPROC)GetProcAddress("glCreateShaderObjectARB");
			glShaderSourceARB         = (PFNGLSHADERSOURCEARBPROC)GetProcAddress("glShaderSourceARB");
			glCompileShaderARB        = (PFNGLCOMPILESHADERARBPROC)GetProcAddress("glCompileShaderARB");
			glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)GetProcAddress("glGetObjectParameterivARB");
			glAttachObjectARB         = (PFNGLATTACHOBJECTARBPROC)GetProcAddress("glAttachObjectARB");
			glGetInfoLogARB           = (PFNGLGETINFOLOGARBPROC)GetProcAddress("glGetInfoLogARB");
			glLinkProgramARB          = (PFNGLLINKPROGRAMARBPROC)GetProcAddress("glLinkProgramARB");
			glGetUniformLocationARB   = (PFNGLGETUNIFORMLOCATIONARBPROC)GetProcAddress("glGetUniformLocationARB");
			glUniform4fARB            = (PFNGLUNIFORM4FARBPROC)GetProcAddress("glUniform4fARB");
			glUniform1iARB            = (PFNGLUNIFORM1IARBPROC)GetProcAddress("glUniform1iARB");

			if( !glCreateProgramObjectARB || !glDeleteObjectARB || !glUseProgramObjectARB ||
				!glCreateShaderObjectARB || !glCreateShaderObjectARB || !glCompileShaderARB || 
				!glGetObjectParameterivARB || !glAttachObjectARB || !glGetInfoLogARB || 
				!glLinkProgramARB || !glGetUniformLocationARB || !glUniform4fARB ||
				!glUniform1iARB )
			{
				GL_CHECK(AESDK_OpenGL_Extensions_Err);
			}
		}
		
#elif defined(AE_OS_MAC)
		Rect rect;
		SetRect(&rect, 0, 0, 50, 50);
		if ( noErr != CreateNewWindow(kDocumentWindowClass, kWindowStandardDocumentAttributes, &rect, &inData.mMacWnd))
			GL_CHECK(AESDK_OpenGL_OS_Load_Err);
		
		GLint aAttribs[64];
		u_short nIndexS= -1;

		// NO color index support
		aAttribs[++nIndexS]= AGL_RGBA;
		// double buffering
		aAttribs[++nIndexS]=AGL_DOUBLEBUFFER;
	    
		// color
		aAttribs[++nIndexS] = AGL_RED_SIZE;
		aAttribs[++nIndexS] = 8;
		aAttribs[++nIndexS] = AGL_GREEN_SIZE;
		aAttribs[++nIndexS] = 8;
		aAttribs[++nIndexS] = AGL_BLUE_SIZE;
		aAttribs[++nIndexS] = 8;
		aAttribs[++nIndexS] = AGL_ALPHA_SIZE;
		aAttribs[++nIndexS] = 8;
	    
		aAttribs[++nIndexS] = AGL_NONE;

		// get an appropriate pixel format
		AGLPixelFormat oPixelFormat = aglChoosePixelFormat(	NULL,
															0,
															aAttribs);
		if( oPixelFormat == NULL )
			GL_CHECK(AESDK_OpenGL_OS_Load_Err);
	    
		// create the context from the pixel format
		inData.mAGLContext = aglCreateContext(oPixelFormat,NULL);
	    
		if( NULL == inData.mAGLContext )
			GL_CHECK(AESDK_OpenGL_Extensions_Err);
	    
		// otherwise clean-up the pixel format
		aglDestroyPixelFormat(oPixelFormat);

		//attach the window
		if ( !aglSetDrawable (inData.mAGLContext, GetWindowPort(inData.mMacWnd)) )
			GL_CHECK(AESDK_OpenGL_Extensions_Err);

		glFlush();
		aglSetCurrentContext(inData.mAGLContext);
#endif
	}
	catch(AESDK_OpenGL_Err& err)
	{
		result = err;
	}

	return result;
}