int WINAPI WinMain(	HINSTANCE hinstance,
                   HINSTANCE hprevinstance,
                   LPSTR lpcmdline,
                   int ncmdshow)
{
    // this is the winmain function
    WNDCLASSEX winclass; // this will hold the class we create
    HWND	   hwnd;	 // generic window handle
    MSG		   msg;		 // generic message
    HDC        hdc;      // graphics device context

    // first fill in the window class stucture
    winclass.cbSize         = sizeof(WNDCLASSEX);
    winclass.style			= CS_DBLCLKS | CS_OWNDC | 
        CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc	= WindowProc;
    winclass.cbClsExtra		= 0;
    winclass.cbWndExtra		= 0;
    winclass.hInstance		= hinstance;
    winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
    winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
    winclass.lpszMenuName	= NULL;
    winclass.lpszClassName	= WINDOW_CLASS_NAME;
    winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    // register the window class
    if (!RegisterClassEx(&winclass))
        return(0);

    // create the window
    if (!(hwnd = CreateWindowEx(NULL,              // extended style
        WINDOW_CLASS_NAME, // class
        WINDOW_TITLE, // title
        (WINDOWED_APP ? (WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION) : (WS_POPUP | WS_VISIBLE)), 
        0,0,	  // initial x,y
        WINDOW_WIDTH,WINDOW_HEIGHT,  // initial width, height
        NULL,	  // handle to parent 
        NULL,	  // handle to menu
        hinstance,// instance of this application
        NULL)))   // extra creation parms
        return(0);

    // save the window handle and instance in a global
    main_window_handle = hwnd;
    main_instance      = hinstance;

    // resize the window so that client is really width x height
    if (WINDOWED_APP)
    {
        // now resize the window, so the client area is the actual size requested
        // since there may be borders and controls if this is going to be a windowed app
        // if the app is not windowed then it won't matter
        RECT window_rect = {0,0,WINDOW_WIDTH-1,WINDOW_HEIGHT-1};


        // make the call to adjust window_rect
        AdjustWindowRectEx(&window_rect,
            GetWindowStyle(main_window_handle),
            GetMenu(main_window_handle) != NULL,
            GetWindowExStyle(main_window_handle));

        // save the global client offsets, they are needed in DDraw_Flip()
        window_client_x0 = -window_rect.left;
        window_client_y0 = -window_rect.top;

        // now resize the window with a call to MoveWindow()
        MoveWindow(main_window_handle,
            0, // x position
            0, // y position
            window_rect.right - window_rect.left, // width
            window_rect.bottom - window_rect.top, // height
            FALSE);

        // show the window, so there's no garbage on first render
        ShowWindow(main_window_handle, SW_SHOW);
    } // end if windowed

    // perform all game console specific initialization
    Game_Init();

    // enter main event loop
    while(1)
    {
        if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        { 
            // test if this is a quit
            if (msg.message == WM_QUIT)
                break;

            // translate any accelerator keys
            TranslateMessage(&msg);

            // send the message to the window proc
            DispatchMessage(&msg);
        } // end if

        // main game processing goes here
        Game_Main();

    } // end while

    // shutdown game and release all resources
    Game_Shutdown();


    // return to Windows like this
    return(msg.wParam);

} // end WinMain