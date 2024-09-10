// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

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

// save hinstance in global
hinstance_app = hinstance;

// register the window class
if (!RegisterClassEx(&winclass))
	return(0);

// create the window
if (!(hwnd = CreateWindowEx(NULL,                // extended style
                            WINDOW_CLASS_NAME,   // class
						    "Polygon Drawing Demo", // title
						    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					 	    0,0,	  // initial x,y
						    WINDOW_WIDTH, // initial width
                            WINDOW_HEIGHT,// initial height
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hinstance,// instance of this application
						    NULL)))	// extra creation parms
return(0);

// save main window handle
main_window_handle = hwnd;

// get the graphics device context 
hdc = GetDC(hwnd);


// enter main event loop, but this time we use PeekMessage()
// instead of GetMessage() to retrieve messages
while(TRUE)
	{
    // test if there is a message in queue, if so get it
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

    // select random colors for polygon 
    HPEN   pen_color   = CreatePen(PS_SOLID, 1, RGB(rand()%256,rand()%256,rand()%256));
    HBRUSH brush_color = CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));

    // select them into dc
    SelectObject(hdc,pen_color);
    SelectObject(hdc,brush_color);

    // now create list of random points for polygon
    int num_points = 3+rand()%8;

    // this will hold the point list
    POINT point_list[10];
 
    // create array of points
    for (int index = 0; index < num_points; index++)
        {
        // set next random point in list
        point_list[index].x = rand()%WINDOW_WIDTH;
        point_list[index].y = rand()%WINDOW_HEIGHT;
        } // end for index
    
    // draw the polygon
    Polygon(hdc, point_list, num_points);

    // let user see it
    Sleep(500);

    // main game processing goes here
    if (KEYDOWN(VK_ESCAPE))
       SendMessage(hwnd, WM_CLOSE, 0,0);
       
	} // end while


// release the device context
ReleaseDC(hwnd,hdc);

// return to Windows like this
return(msg.wParam);

} // end WinMain