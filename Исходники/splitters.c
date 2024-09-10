LRESULT CALLBACK SpltWe_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int  oldx;
    static int y;
    static int line_height;
    static int min_left;
    static int max_right;
    POINT pt;
    HDC hdc;
    RECT rect;
    HWND hp = GetParent(hwnd);



        
        switch (message)
        {
            case WM_CREATE:

                return 0 ;

    case WM_LBUTTONDOWN:
        SetCapture(hwnd);
        we_sizing = 1;
        line_height = win_height(hwnd);
        y = win_top(hwnd);;
    pt.x = (short)LOWORD(lParam);  // horizontal position of cursor 
    pt.y = (short)HIWORD(lParam);

    GetWindowRect(hp,&rect);
    min_left = rect.left + MIN_SPLT_SPACE;
    max_right = rect.right - MIN_SPLT_SPACE;
    //GetClientRect(hwnd,&splt_rect);
    //SCreenToClient(rect);

    //GetWindowRect(hwnd_frame, &rect_frame_scr);
    //client_0_0.x = 0;
    //client_0_0.y=0;
    //ClientToScreen(hwnd_frame,&client_0_0);
    //client_0_0.y-= rect_frame_scr.top;
    //client_0_0.x-= rect_frame_scr.left;

    ClientToScreen(hwnd,&pt);


    //convert the mouse coordinates relative to the top-left of
    //the window
    //ScreenToClient(hwnd_frame,&pt);

    if(pt.x < min_left) pt.x = min_left;
    if(pt.x > max_right) 
    {
        pt.x = max_right;
    }


    hdc = GetDC(NULL);
    DrawXorBar(hdc, pt.x-SPLT_WIDTH/2, y, SPLT_WIDTH, line_height);
    ReleaseDC(NULL, hdc);

    oldx = pt.x;

    break;

    case WM_LBUTTONUP:
        ReleaseCapture();

    pt.x = (short)LOWORD(lParam);  // horizontal position of cursor 
    pt.y = (short)HIWORD(lParam);

    GetClientRect(hp,&rect);
    //GetClientRect(hwnd,&splt_rect);

    //GetWindowRect(hwnd_frame, &rect_frame_scr);
    //client_0_0.x = 0;
    //client_0_0.y=0;
    //ClientToScreen(hwnd_frame,&client_0_0);
    //client_0_0.y-= rect_frame_scr.top;
    //client_0_0.x-= rect_frame_scr.left;

    hdc = GetDC(NULL);
    DrawXorBar(hdc, oldx-SPLT_WIDTH/2, y, SPLT_WIDTH, line_height);
    ReleaseDC(NULL, hdc);


    we_sizing = 0;
    pt.x = oldx;
    ScreenToClient(hp,&pt);
    send_splitter_x(hp, pt.x);
    break;

    case WM_MOUSEMOVE:
    if(0==we_sizing)  break;

    pt.x = (short)LOWORD(lParam);  // horizontal position of cursor 
    pt.y = (short)HIWORD(lParam);

    //GetClientRect(hwnd_frame,&rect);
    //GetClientRect(hwnd,&splt_rect);
    //SCreenToClient(rect);
    ClientToScreen(hwnd,&pt);

    //GetWindowRect(hwnd_frame, &rect_frame_scr);
    //client_0_0.x = 0;
    //client_0_0.y=0;
    //ClientToScreen(hwnd_frame,&client_0_0);
    //client_0_0.y-= rect_frame_scr.top;
    //client_0_0.x-= rect_frame_scr.left;


    //convert the mouse coordinates relative to the top-left of
    //the window
    //ScreenToClient(hwnd_frame,&pt);

    if(pt.x < min_left) pt.x = min_left;
    if(pt.x > max_right) 
    {
        pt.x = max_right;
    }




    if(pt.x != oldx && wParam & MK_LBUTTON)
    {
    hdc = GetDC(NULL);
    DrawXorBar(hdc, oldx-SPLT_WIDTH/2, y, SPLT_WIDTH, line_height);
    DrawXorBar(hdc, pt.x-SPLT_WIDTH/2, y, SPLT_WIDTH, line_height);
    ReleaseDC(NULL, hdc);

    oldx = pt.x;
    }

    break;

    }
        
        return DefWindowProc (hwnd, message, wParam, lParam) ;
    }