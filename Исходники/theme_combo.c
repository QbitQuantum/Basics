/**********************************************************************
 * The combo control subclass window proc.
 */
LRESULT CALLBACK THEMING_ComboSubclassProc (HWND hwnd, UINT msg, 
                                            WPARAM wParam, LPARAM lParam, 
                                            ULONG_PTR dwRefData)
{
    const WCHAR* themeClass = WC_COMBOBOXW;
    HTHEME theme;
    LRESULT result;
      
    switch (msg)
    {
    case WM_CREATE:
        result = THEMING_CallOriginalClass  (hwnd, msg, wParam, lParam);
        OpenThemeData( hwnd, themeClass );
        return result;
    
    case WM_DESTROY:
        theme = GetWindowTheme( hwnd );
        CloseThemeData ( theme );
        return THEMING_CallOriginalClass (hwnd, msg, wParam, lParam);

    case WM_THEMECHANGED:
        theme = GetWindowTheme( hwnd );
        CloseThemeData ( theme );
        OpenThemeData( hwnd, themeClass );
        break;
        
    case WM_SYSCOLORCHANGE:
        theme = GetWindowTheme( hwnd );
	if (!theme) return THEMING_CallOriginalClass (hwnd, msg, wParam, lParam);
        /* Do nothing. When themed, a WM_THEMECHANGED will be received, too,
   	 * which will do the repaint. */
        break;
        
    case WM_PAINT:
        theme = GetWindowTheme( hwnd );
        if (!theme) return THEMING_CallOriginalClass (hwnd, msg, wParam, lParam);
        return paint (theme, hwnd, (HDC)wParam, dwRefData);

    case WM_SETREDRAW:
        /* Since there doesn't seem to be WM_GETREDRAW, do redraw tracking in 
         * the subclass as well. */
        if( wParam )
            dwRefData &= ~STATE_NOREDRAW;
        else
            dwRefData |= STATE_NOREDRAW;
        THEMING_SetSubclassData (hwnd, dwRefData);
        return THEMING_CallOriginalClass (hwnd, msg, wParam, lParam);
        
    case WM_MOUSEMOVE:
        {
            /* Dropdown button hot-tracking */
            COMBOBOXINFO cbi;
            POINT pt;

            pt.x = (short)LOWORD(lParam);
            pt.y = (short)HIWORD(lParam);
            cbi.cbSize = sizeof (cbi);
            SendMessageW (hwnd, CB_GETCOMBOBOXINFO, 0, (LPARAM)&cbi);
            
            if (cbi.stateButton != STATE_SYSTEM_INVISIBLE)
            {
                if (PtInRect (&cbi.rcButton, pt))
                {
                    if (!(dwRefData & STATE_HOT))
                    {
                        dwRefData |= STATE_HOT;
                        THEMING_SetSubclassData (hwnd, dwRefData);
                        RedrawWindow (hwnd, &cbi.rcButton, 0, 
                            RDW_INVALIDATE | RDW_UPDATENOW);
                    }
                }
                else
                {
                    if (dwRefData & STATE_HOT)
                    {
                        dwRefData &= ~STATE_HOT;
                        THEMING_SetSubclassData (hwnd, dwRefData);
                        RedrawWindow (hwnd, &cbi.rcButton, 0, 
                            RDW_INVALIDATE | RDW_UPDATENOW);
                    }
                }
            }
        }
        return THEMING_CallOriginalClass (hwnd, msg, wParam, lParam);
    
    default: 
	/* Call old proc */
	return THEMING_CallOriginalClass (hwnd, msg, wParam, lParam);
    }
    return 0;
}