  //*************************************************************************//
  long Graphics::Initialize(HWND hWindow, unsigned long ulWidth, unsigned long ulHeight)										
  {
    //-----------------------------------------------------------------------//
    // Create a data member to hold the result of this method. In this method's
    // case it will hold any error codes. By default set to 1 to signal no error. 
    long lResultCode = 1;
    //-----------------------------------------------------------------------//

    smhWindow = hWindow;

    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
    {
      sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
      1,											// Version Number
      PFD_DRAW_TO_WINDOW |						// Format Must Support Window
      PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
      PFD_DOUBLEBUFFER,							// Must Support Double Buffering
      PFD_TYPE_RGBA,								// Request An RGBA Format
      32,										// Select Our Color Depth
      0, 0, 0, 0, 0, 0,							// Color Bits Ignored
      0,											// No Alpha Buffer
      0,											// Shift Bit Ignored
      0,											// No Accumulation Buffer
      0, 0, 0, 0,									// Accumulation Bits Ignored
      16,											// 16Bit Z-Buffer (Depth Buffer)  
      0,											// No Stencil Buffer
      0,											// No Auxiliary Buffer
      PFD_MAIN_PLANE,								// Main Drawing Layer
      0,											// Reserved
      0, 0, 0										// Layer Masks Ignored
    };

    GLuint		PixelFormat;
    if(!(smhDeviceContext = GetDC(hWindow)))
    {
      lResultCode = -1;
      smhDeviceContext = NULL;
    }

    if(lResultCode > 0 && !(PixelFormat = ChoosePixelFormat(smhDeviceContext, &pfd)))	// Did Windows Find A Matching Pixel Format?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !SetPixelFormat(smhDeviceContext, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !(smhRenderingContext = wglCreateContext(smhDeviceContext)))				// Are We Able To Get A Rendering Context?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !wglMakeCurrent(smhDeviceContext, smhRenderingContext))					// Try To Activate The Rendering Context
    {
      lResultCode = -1;
    }

    if(lResultCode > 0)
    {
      // Check Required Extensions
      GLenum err = glewInit();
      if(err == GLEW_OK)
      {
        glewGetString(GLEW_VERSION);
        /// \TODO DO something with version.
        if(GLEW_ARB_vertex_buffer_object)
        {
          
          glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
          glClearDepth(1.0f);									// Depth Buffer Setup
          glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
          glEnable ( GL_LIGHTING ) ;
          float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
          glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
          GLfloat specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
          glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
          glShadeModel(GL_SMOOTH);

          glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
          glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
          glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
          glEnable(GL_TEXTURE_2D);

          glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, reinterpret_cast<GLint*>(&(smuiMaxNumberOfVertexElements)));
          glGetIntegerv(GL_MAX_ELEMENTS_INDICES, reinterpret_cast<GLint*>(&(smuiMaxNumberOfIndexElements)));
        }
        else
        {
          lResultCode = -1;
        }
      }
      else
      {
        glewGetErrorString(err);
        lResultCode = -1;
        /// \TODO do something with error.
      }
    }

    //-----------------------------------------------------------------------//
    // Return result/error code
    return lResultCode;
    //-----------------------------------------------------------------------//
  } // End of long Graphics::Initialize(HWND hWindow)	