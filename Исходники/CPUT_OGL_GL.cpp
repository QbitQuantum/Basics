HWND CPUT_OGL::CreateDummyWindow(HINSTANCE hInst)
{
    WNDCLASS  Window;      // Window class
    uint32    PixelFormat; // Format of pixel
    
    // Window settings
    Window.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Have its own Device Context and also cannot be resized    
    Window.lpfnWndProc   = (WNDPROC) WndProcDummy;              // Procedure that handles OS evets
    Window.cbClsExtra    = 0;                                   // No extra window data
    Window.cbWndExtra    = 0;                                   //
    Window.hInstance     = hInst;                               // Handle to instance of program that this window belongs to
    Window.hIcon         = LoadIcon(NULL, IDI_WINLOGO);         // Load default icon
    Window.hCursor       = LoadCursor(NULL, IDC_ARROW);         // Load arrow pointer
    Window.hbrBackground = NULL;                                // No background (OpenGL will handle this)
    Window.lpszMenuName  = NULL;                                // No menu
    Window.lpszClassName = L"DummyWindowClass";                 // Class name
    
    // Registering Window Class
    if ( !RegisterClass( &Window ) )	
    {					
        cerr << "Error! Cannot register window class." << endl;
        return NULL;
    }

    // Create Dummy Window with OpenGL RC to gather required
    // information together with wgl functions pointers and
    // final Pixel Format number.
    HWND hWnd = CreateWindow(
        L"DummyWindowClass",           // Window class name
        L"CPUTFramework...",           // Title of window            
        WS_CLIPSIBLINGS |             // \_Prevents from overdrawing
        WS_CLIPCHILDREN |             // / by other windows
        WS_OVERLAPPEDWINDOW,          // Additional styles
        0, 0,                         // Position
        128,                          // True window widht
        128,                          // True window height
        NULL,                         // No parent window
        NULL,                         // No menu
        hInst,                        // Handle to this instance of program
        NULL );                       // Won't pass anything
    
    // Check if dummy window was created
    if ( hWnd == NULL )
    {
        cerr << "Error! Cannot create window." << endl;
        DestroyOGLContext();	
        return NULL;
    }  
    
    // Acquiring Device Context
    mhDC = GetDC( hWnd );
    if ( mhDC == NULL )
    {
        cerr << "Error! Cannot create device context." << endl;		
        DestroyOGLContext();	
        return NULL;
    }  
    
    // Choosing Pixel Format the old way
    PixelFormat = ChoosePixelFormat( mhDC, &pfdLegacy );
    if ( PixelFormat == NULL )
    {
        cerr << "Error! Cannot find aproprieate pixel format." << endl;	
        DestroyOGLContext();	
        return NULL;
    }  
    
    // Activating Pixel Format
    if ( !SetPixelFormat( mhDC, PixelFormat, &pfdLegacy ) )
    {	
        cerr << "Error! Cannot init pixel format." << endl;
        DestroyOGLContext();		
        return NULL;
    }  
    
    // Creating OpenGL Rendering Context
    mhRC = wglCreateContext( mhDC );
    if ( mhRC == NULL )
    {
        cerr << "Error! Cannot create window rendering context." << endl;
        DestroyOGLContext();						
        return NULL;
    }  
    
    // Activating rendering context
    if ( !wglMakeCurrent( mhDC, mhRC ) )
    {	
        cerr << "Error! Cannot activate rendering context." << endl;
        DestroyOGLContext();	
        return NULL;
    } 
    
    return hWnd;
}