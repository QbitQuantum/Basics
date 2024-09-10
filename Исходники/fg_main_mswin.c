SFG_Window* fghWindowUnderCursor(SFG_Window *window)
{
    /* Check if the current window that the mouse is over is a child window
     * of the window the message was sent to. Some events only sent to main window,
     * and when handling some messages, we need to make sure that we process
     * callbacks on the child window instead. This mirrors how GLUT does things.
     * returns either the original window or the found child.
     */
    if (window && window->Children.First)   /* This window has childs */
    {
        HWND hwnd;
        SFG_Window* child_window;

        /* Get mouse position at time of message */
        DWORD mouse_pos_dw = GetMessagePos();
        POINT mouse_pos = {GET_X_LPARAM(mouse_pos_dw), GET_Y_LPARAM(mouse_pos_dw)};
        ScreenToClient( window->Window.Handle, &mouse_pos );
        
        hwnd = ChildWindowFromPoint(window->Window.Handle, mouse_pos);
        if (hwnd && hwnd!=window->Window.Handle)   /* can be NULL if mouse outside parent by the time we get here, or can be same as parent if we didn't find a child */
        {
            child_window = fgWindowByHandle(hwnd);
            if (child_window)    /* Verify we got a FreeGLUT window */
            {
                /* ChildWindowFromPoint only searches immediate children, so search again to see if actually in grandchild or further descendant */
                window = fghWindowUnderCursor(child_window);
            }
        }
    }

    return window;
}