/**********************************************************************
 * The dialog subclass window proc.
 */
LRESULT CALLBACK THEMING_DialogSubclassProc (HWND hWnd, UINT msg, 
                                             WPARAM wParam, LPARAM lParam, 
                                             ULONG_PTR dwRefData)
{
    HTHEME theme = GetWindowTheme ( hWnd );
    static const WCHAR themeClass[] = { 'W','i','n','d','o','w',0 };
    BOOL themingActive = IsThemeDialogTextureEnabled (hWnd);
    BOOL doTheming = themingActive && (theme != NULL);
    LRESULT result;
      
    switch (msg)
    {
    case WM_CREATE:
	result = THEMING_CallOriginalClass (hWnd, msg, wParam, lParam);
	theme = OpenThemeData( hWnd, themeClass );
	return result;
    
    case WM_DESTROY:
        CloseThemeData ( theme );
        SetWindowTheme( hWnd, NULL, NULL );
        OpenThemeData( hWnd, NULL );
        return THEMING_CallOriginalClass (hWnd, msg, wParam, lParam);

    case WM_THEMECHANGED:
        CloseThemeData ( theme );
	OpenThemeData( hWnd, themeClass );
	InvalidateRect( hWnd, NULL, TRUE );
	return 0;
	
    case WM_SYSCOLORCHANGE:
	if (!doTheming) return THEMING_CallOriginalClass (hWnd, msg, wParam, lParam);
        /* Do nothing. When themed, a WM_THEMECHANGED will be received, too,
   	 * which will do the repaint. */
        break;
        
    case WM_ERASEBKGND:
	if (!doTheming) return THEMING_CallOriginalClass (hWnd, msg, wParam, lParam);
        {
            RECT rc;
            WNDPROC dlgp = (WNDPROC)GetWindowLongPtrW (hWnd, DWLP_DLGPROC);
            if (!CallWindowProcW(dlgp, hWnd, msg, wParam, lParam))
            {
                /* Draw background*/
                GetClientRect (hWnd, &rc);
                if (IsThemePartDefined (theme, WP_DIALOG, 0))
                    /* Although there is a theme for the WINDOW class/DIALOG part, 
                     * but I[res] haven't seen Windows using it yet... Even when
                     * dialog theming is activated, the good ol' BTNFACE 
                     * background seems to be used. */
#if 0
                    DrawThemeBackground (theme, (HDC)wParam, WP_DIALOG, 0, &rc, 
                        NULL);
#endif
                    return THEMING_CallOriginalClass (hWnd, msg, wParam, lParam);
                else 
                /* We might have gotten a TAB theme class, so check if we can 
                 * draw as a tab page. */
                if (IsThemePartDefined (theme, TABP_BODY, 0))
                    DrawThemeBackground (theme, (HDC)wParam, TABP_BODY, 0, &rc, 
                        NULL);
                else
                    return THEMING_CallOriginalClass (hWnd, msg, wParam, lParam);
            }
            return 1;
        }