/*****************************************************************
 *		SetFocus  (USER32.@)
 */
HWND WINAPI SetFocus( HWND hwnd )
{
    HWND hwndTop = hwnd;
    HWND previous = GetFocus();

    TRACE( "%p prev %p\n", hwnd, previous );

    if (hwnd)
    {
        /* Check if we can set the focus to this window */
        hwnd = WIN_GetFullHandle( hwnd );
        if (!IsWindow( hwnd ))
        {
            SetLastError( ERROR_INVALID_WINDOW_HANDLE );
            return 0;
        }
        if (hwnd == previous) return previous;  /* nothing to do */
        for (;;)
        {
            HWND parent;
            LONG style = GetWindowLongW( hwndTop, GWL_STYLE );
            if (style & (WS_MINIMIZE | WS_DISABLED)) return 0;
            if (!(style & WS_CHILD)) break;
            parent = GetAncestor( hwndTop, GA_PARENT );
            if (!parent || parent == GetDesktopWindow())
            {
                if ((style & (WS_POPUP|WS_CHILD)) == WS_CHILD) return 0;
                break;
            }
            if (parent == get_hwnd_message_parent()) return 0;
            hwndTop = parent;
        }

        /* call hooks */
        if (HOOK_CallHooks( WH_CBT, HCBT_SETFOCUS, (WPARAM)hwnd, (LPARAM)previous, TRUE )) return 0;

        /* activate hwndTop if needed. */
        if (hwndTop != GetActiveWindow())
        {
            if (!set_active_window( hwndTop, NULL, FALSE, FALSE )) return 0;
            if (!IsWindow( hwnd )) return 0;  /* Abort if window destroyed */

            /* Do not change focus if the window is no longer active */
            if (hwndTop != GetActiveWindow()) return 0;
        }
    }
    else /* NULL hwnd passed in */
    {
        if (!previous) return 0;  /* nothing to do */
        if (HOOK_CallHooks( WH_CBT, HCBT_SETFOCUS, 0, (LPARAM)previous, TRUE )) return 0;
    }

    /* change focus and send messages */
    return set_focus_window( hwnd );
}