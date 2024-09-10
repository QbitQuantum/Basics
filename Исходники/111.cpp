/*This is the WinMain function. Here we will create the rendering window, initialize OpenGL ES, write the message loop, and, at the end, clean all and release all used resources*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,	int nCmdShow)
{
  MSG msg; //This is the message variable for the message loop
  WNDCLASS	wc; /*This structure will hold some init values for our window*/
  hInst = hInstance; // Initialization of our global variable
  bool done = FALSE; 
	  
  /*This block of code is to ensure that the user only can run one
    instance of the application. First we search for a window with the 
    same class name, if found, we will focus it and return*/
  if(hWnd = FindWindow(szAppName, szAppName)) 
  {
    /* Set focus to foremost child window. The "| 0x01" is used to 
       bring any owned windows to the foreground and activate them.*/
    SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
    return 0;
  } 
		
  wc.style          = CS_HREDRAW | CS_VREDRAW; /*Will force a redraw 
  if the window is resized, both horizontally or vertically*/
  wc.lpfnWndProc    = (WNDPROC) WndProc; /*this is a function pointer,
  to tell the OS what function should call when a message needs to be 
  processed*/
  wc.cbClsExtra     = 0;
  wc.cbWndExtra     = 0;
  wc.hInstance      = hInstance;
  wc.hIcon          = LoadIcon(hInstance, NULL);//Load default icon
  wc.hCursor	      = 0; // Default cursor
  wc.hbrBackground  = 0; //We don't care about the background color
  wc.lpszMenuName	  = NULL; //This application does not have a menu
  wc.lpszClassName  = szAppName; /*Important, here we must fill the
   application class name (the class name is not the same than the 
   caption of the window, but many times they are the same)*/

  //Before creating the window, we must register this new window class
  if(!RegisterClass(&wc))
    return FALSE;
	
  hWnd=CreateWindow(szAppName, //Class Name
                    szAppName, //Caption string
                    WS_VISIBLE,//Window style
                    CW_USEDEFAULT,CW_USEDEFAULT,//Starting [x,y] pos.
                    CW_USEDEFAULT, CW_USEDEFAULT, //Width and height
                    NULL, NULL, //Parent window and menu handle
                    hInst, NULL); /*Instance handle. Custom value to 
                    pass in the creation with the WM_CREATE message*/
	                  
  if(!hWnd) return FALSE;
  if(!InitOGLES()) return FALSE; //OpenGL ES Initialization
  
  //Bring the window to front, focus it and refresh it
  ShowWindow(hWnd, nCmdShow); 
  UpdateWindow(hWnd);
 
  //Message Loop
  while(!done)
  {
    if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
    {
      if(msg.message==WM_QUIT)
        done=TRUE;
	    else
      { 
	      TranslateMessage(&msg);
	      DispatchMessage(&msg);
	    }
    }
    else										
	    Render();
  }
  //Clean up all
  Clean();
  return 0;
}