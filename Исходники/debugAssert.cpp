void _releaseInputGrab_() {
    #ifdef G3D_WIN32

        GetCursorPos(&oldCursorPos);

        // Stop hiding the cursor if the application hid it.
        oldShowCursorCount = ShowCursor(true) - 1;

        if (oldShowCursorCount < -1) {
            for (int c = oldShowCursorCount; c < -1; ++c) {
                ShowCursor(true);
            }
        }

        // Set the default cursor in case the application
        // set the cursor to NULL.
        oldCursor = GetCursor();
        SetCursor(LoadCursor(NULL, IDC_ARROW));

        // Allow the cursor full access to the screen
        GetClipCursor(&oldCursorRect);
        ClipCursor(NULL);

    #elif defined(G3D_LINUX)
#if 0 /* G3DFIX: Disabled to avoid requirement for X11 libraries */
        if (x11Display != NULL) {
            XUngrabPointer(x11Display, CurrentTime);
            XUngrabKeyboard(x11Display, CurrentTime);
            if (x11Window != 0) {
                //XUndefineCursor(x11Display, x11Window);
                // TODO: Note that we leak this cursor; it should be
                // freed in the restore code.
                Cursor c = XCreateFontCursor(x11Display, 68);
                XDefineCursor(x11Display, x11Window, c);
            }
            XSync(x11Display, false);
            XAllowEvents(x11Display, AsyncPointer, CurrentTime);
            XFlush(x11Display);
        }
#endif
    #elif defined(G3D_OSX)
        // TODO: OS X
    #endif
}