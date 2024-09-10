// callback function for the splitter window.
LRESULT	CALLBACK 
TabEditorSplitter::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	TabEditorSplitter	*ptabsplitter =(TabEditorSplitter*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    HBRUSH hbr;
    RECT rc;

	switch(message)
	{
    case WM_NCCREATE:
		// Get the initial creation pointer to the window object
		ptabsplitter = (TabEditorSplitter *)((CREATESTRUCT *)lparam)->lpCreateParams;        
		ptabsplitter->m_hwnd = hwnd;
		SetWindowLongPtr(hwnd, GWLP_USERDATA,(LONG_PTR)ptabsplitter);
        break;

	case WM_PAINT:
		return ptabsplitter->OnPaint();
		
	case WM_MOUSEMOVE:
		ptabsplitter->MouseMove();
		return 0;
	
    case WM_MOVE:
        //return ptabsplitter->OnPaint();
        InvalidateRect(ptabsplitter->m_hwnd, NULL, FALSE);  // hav to test it
        UpdateWindow(hwnd);
        return 0;

	case WM_LBUTTONDOWN:
        ptabsplitter->m_hwndprevfocus = GetFocus();
        ptabsplitter->m_prevstyle = GetWindowLongPtr(ptabsplitter->m_hwndparent, GWL_STYLE);
        SetWindowLongPtr(ptabsplitter->m_hwndparent, GWL_STYLE, ptabsplitter->m_prevstyle & ~WS_CLIPCHILDREN);
        SetFocus(hwnd);
		SetCapture(hwnd);
		ptabsplitter->m_isdragged	= wyTrue;
        ptabsplitter->MouseMove(wyTrue);
		break;

	case WM_LBUTTONUP:
		ReleaseCapture();
		break;

	case WM_CAPTURECHANGED:
		if(ptabsplitter->m_isdragged == wyTrue)
		{
            ptabsplitter->EndDrag(wyTrue);
            SetWindowLongPtr(ptabsplitter->m_hwndparent, GWL_STYLE, ptabsplitter->m_prevstyle);

			if(ptabsplitter->m_isdlgsplitter == wyTrue)
				PostMessage(GetParent(hwnd), UM_SPLITTERRESIZED, 0, 0);
			else
			{
                ptabsplitter->Resizeall();
				InvalidateRect(hwnd, NULL, TRUE);
				UpdateWindow(hwnd);
			}

			ptabsplitter->m_isdragged = wyFalse;

            if(ptabsplitter->m_hwndprevfocus)
            {
                SetFocus(ptabsplitter->m_hwndprevfocus);
                ptabsplitter->m_hwndprevfocus = NULL;
            }
		}
		break;

    case WM_ERASEBKGND:
        if(ptabsplitter->m_isdlgsplitter == wyFalse &&
            wyTheme::GetBrush(BRUSH_HSPLITTER, &hbr))
        {
            GetClientRect(hwnd, &rc);
            FillRect((HDC)wparam, &rc, hbr);
            return 1;
        }
	}
			
	return(DefWindowProc(hwnd, message, wparam, lparam));
}