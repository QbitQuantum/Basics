static int
icvCreateTrackbar( const char* trackbar_name, const char* window_name,
                   int* val, int count, CvTrackbarCallback on_notify,
                   CvTrackbarCallback2 on_notify2, void* userdata )
{
    int result = 0;

    CV_FUNCNAME( "icvCreateTrackbar" );

    __BEGIN__;

    char slider_name[32];
    CvWindow* window = 0;
    CvTrackbar* trackbar = 0;
    int pos = 0;

    if( !window_name || !trackbar_name )
        CV_ERROR( CV_StsNullPtr, "NULL window or trackbar name" );

    if( count <= 0 )
        CV_ERROR( CV_StsOutOfRange, "Bad trackbar maximal value" );

    window = icvFindWindowByName(window_name);
    if( !window )
        EXIT;

    trackbar = icvFindTrackbarByName(window,trackbar_name);
    if( !trackbar )
    {
        TBBUTTON tbs;
        ButtonInfo tbis;
        RECT rect;
        int bcount;
        int len = (int)strlen( trackbar_name );

        // create toolbar if it is not created yet
        if( !window->toolbar.toolbar )
        {
            const int default_height = 30;

            window->toolbar.toolbar = CreateToolbarEx(
                    window->frame, WS_CHILD | CCS_TOP | TBSTYLE_WRAPABLE,
                    1, 0, 0, 0, 0, 0, 16, 20, 16, 16, sizeof(TBBUTTON));
            GetClientRect(window->frame, &rect);
            MoveWindow( window->toolbar.toolbar, 0, 0,
                        rect.right - rect.left, default_height, TRUE);
            SendMessage(window->toolbar.toolbar, TB_AUTOSIZE, 0, 0);
            ShowWindow(window->toolbar.toolbar, SW_SHOW);

            window->toolbar.first = 0;
            window->toolbar.pos = 0;
            window->toolbar.rows = 0;
            window->toolbar.toolBarProc =
                (WNDPROC)icvGetWindowLongPtr(window->toolbar.toolbar, CV_WNDPROC);

            icvUpdateWindowPos(window);

            // Subclassing from toolbar
            icvSetWindowLongPtr(window->toolbar.toolbar, CV_WNDPROC, HGToolbarProc);
            icvSetWindowLongPtr(window->toolbar.toolbar, CV_USERDATA, window);
        }

        /* Retrieve current buttons count */
        bcount = (int)SendMessage(window->toolbar.toolbar, TB_BUTTONCOUNT, 0, 0);

        if(bcount > 1)
        {
            /* If this is not the first button then we need to
            separate it from the previous one */
            tbs.iBitmap = 0;
            tbs.idCommand = bcount; // Set button id to it's number
            tbs.iString = 0;
            tbs.fsStyle = TBSTYLE_SEP;
            tbs.fsState = TBSTATE_ENABLED;
            SendMessage(window->toolbar.toolbar, TB_ADDBUTTONS, 1, (LPARAM)&tbs);

            // Retrieve current buttons count
            bcount = (int)SendMessage(window->toolbar.toolbar, TB_BUTTONCOUNT, 0, 0);
        }

        /* Add a button which we're going to cover with the slider */
        tbs.iBitmap = 0;
        tbs.idCommand = bcount; // Set button id to it's number
        tbs.fsState = TBSTATE_ENABLED;
#if 0/*!defined WIN64 && !defined EM64T*/
        tbs.fsStyle = 0;
        tbs.iString = 0;
#else

#ifndef TBSTYLE_AUTOSIZE
#define TBSTYLE_AUTOSIZE        0x0010
#endif

#ifndef TBSTYLE_GROUP
#define TBSTYLE_GROUP           0x0004
#endif
        //tbs.fsStyle = TBSTYLE_AUTOSIZE;
        tbs.fsStyle = TBSTYLE_GROUP;
        tbs.iString = (INT_PTR)trackbar_text;
#endif
        SendMessage(window->toolbar.toolbar, TB_ADDBUTTONS, 1, (LPARAM)&tbs);

        /* Adjust button size to the slider */
        tbis.cbSize = sizeof(tbis);
        tbis.dwMask = TBIF_SIZE;

        GetClientRect(window->hwnd, &rect);
        tbis.cx = (unsigned short)(rect.right - rect.left);

        SendMessage(window->toolbar.toolbar, TB_SETBUTTONINFO,
            (WPARAM)tbs.idCommand, (LPARAM)&tbis);

        /* Get button position */
        SendMessage(window->toolbar.toolbar, TB_GETITEMRECT,
            (WPARAM)tbs.idCommand, (LPARAM)&rect);

        /* Create a slider */
        trackbar = (CvTrackbar*)cvAlloc( sizeof(CvTrackbar) + len + 1 );
        trackbar->signature = CV_TRACKBAR_MAGIC_VAL;
        trackbar->notify = 0;
        trackbar->notify2 = 0;
        trackbar->parent = window;
        trackbar->pos = 0;
        trackbar->data = 0;
        trackbar->id = bcount;
        trackbar->next = window->toolbar.first;
        trackbar->name = (char*)(trackbar + 1);
        memcpy( trackbar->name, trackbar_name, len + 1 );
        window->toolbar.first = trackbar;

        sprintf(slider_name, "Trackbar%p", val);
        trackbar->hwnd = CreateWindowEx(0, TRACKBAR_CLASS, slider_name,
                            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS |
                            TBS_FIXEDLENGTH | TBS_HORZ | TBS_BOTTOM,
                            rect.left + HG_BUDDY_WIDTH, rect.top,
                            rect.right - rect.left - HG_BUDDY_WIDTH,
                            rect.bottom - rect.top, window->toolbar.toolbar,
                            (HMENU)(size_t)bcount, hg_hinstance, 0);

        sprintf(slider_name,"Buddy%p", val);
        trackbar->buddy = CreateWindowEx(0, "STATIC", slider_name,
                            WS_CHILD | SS_RIGHT,
                            rect.left, rect.top,
                            HG_BUDDY_WIDTH, rect.bottom - rect.top,
                            window->toolbar.toolbar, 0, hg_hinstance, 0);

        icvSetWindowLongPtr( trackbar->hwnd, CV_USERDATA, trackbar );

        /* Minimize the number of rows */
        SendMessage( window->toolbar.toolbar, TB_SETROWS,
                     MAKEWPARAM(1, FALSE), (LPARAM)&rect );
    }
    else
    {
        trackbar->data = 0;
        trackbar->notify = 0;
        trackbar->notify2 = 0;
    }

    trackbar->maxval = count;

    /* Adjust slider parameters */
    SendMessage(trackbar->hwnd, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, count));
    SendMessage(trackbar->hwnd, TBM_SETTICFREQ, (WPARAM)1, (LPARAM)0 );
    if( val )
        pos = *val;

    SendMessage(trackbar->hwnd, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)pos );
    SendMessage(window->toolbar.toolbar, TB_AUTOSIZE, 0, 0);

    trackbar->pos = -1;
    icvUpdateTrackbar( trackbar, pos );
    ShowWindow( trackbar->buddy, SW_SHOW );
    ShowWindow( trackbar->hwnd, SW_SHOW );

    trackbar->notify = on_notify;
    trackbar->notify2 = on_notify2;
    trackbar->userdata = userdata;
    trackbar->data = val;

    /* Resize the window to reflect the toolbar resizing*/
    icvUpdateWindowPos(window);

    result = 1;

    __END__;

    return result;
}