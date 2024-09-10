/*
 * Resize the current window so that it fits the whole screen
 */
void FGAPIENTRY glutFullScreen( void )
{
    freeglut_assert_ready;
    freeglut_assert_window;

    {
#if TARGET_HOST_UNIX_X11
        int x, y;
        Window w;

        XMoveResizeWindow(
            fgDisplay.Display,
            fgStructure.Window->Window.Handle,
            0, 0,
            fgDisplay.ScreenWidth,
            fgDisplay.ScreenHeight
        );

        XFlush( fgDisplay.Display ); /* This is needed */

        XTranslateCoordinates(
            fgDisplay.Display,
            fgStructure.Window->Window.Handle,
            fgDisplay.RootWindow,
            0, 0, &x, &y, &w
        );

        if (x || y)
        {
            XMoveWindow(
                fgDisplay.Display,
                fgStructure.Window->Window.Handle,
                -x, -y
            );
            XFlush( fgDisplay.Display ); /* XXX Shouldn't need this */
        }
#elif TARGET_HOST_WIN32
        RECT rect;

        /* For fullscreen mode, force the top-left corner to 0,0
         * and adjust the window rectangle so that the client area
         * covers the whole screen.
         */

        rect.left   = 0;
        rect.top    = 0;
        rect.right  = fgDisplay.ScreenWidth;
        rect.bottom = fgDisplay.ScreenHeight;

        AdjustWindowRect ( &rect, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |
                                  WS_CLIPCHILDREN, FALSE );

        /*
         * SWP_NOACTIVATE     Do not activate the window
         * SWP_NOOWNERZORDER  Do not change position in z-order
         * SWP_NOSENDCHANGING Supress WM_WINDOWPOSCHANGING message
         * SWP_NOZORDER       Retains the current Z order (ignore 2nd param)
         */

        SetWindowPos( fgStructure.Window->Window.Handle,
                      HWND_TOP,
                      rect.left,
                      rect.top,
                      rect.right  - rect.left,
                      rect.bottom - rect.top,
                      SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING |
                      SWP_NOZORDER
                    );
#endif
    }
}