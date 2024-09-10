// callback function for the splitter window.
LRESULT	CALLBACK 
FrameWindowSplitter::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
   // Get a pointer to the window class object.
    FrameWindowSplitter	*pFrameWindowSplitter = (FrameWindowSplitter *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch(message)
	{
    case WM_NCCREATE:
        // Get the initial creation pointer to the window object
		pFrameWindowSplitter = (FrameWindowSplitter *)((CREATESTRUCT *)lparam)->lpCreateParams;        
		pFrameWindowSplitter->m_hwnd = hwnd;
		SetWindowLongPtr(hwnd, GWLP_USERDATA,(LONG_PTR)pFrameWindowSplitter);
        break;

	case WM_PAINT:
		return pFrameWindowSplitter->OnPaint();
		
	case WM_MOUSEMOVE:
		pFrameWindowSplitter->MouseMove();
		return 0;

	case WM_LBUTTONDOWN:
		{
			MDIWindow * pcquerywnd = (MDIWindow*)GetWindowLongPtr(pFrameWindowSplitter->m_hwndparent, GWLP_USERDATA);
			if(pcquerywnd->m_isobjbrowvis == wyFalse)
				break;
			else
			{
                pFrameWindowSplitter->m_prevstyle = GetWindowLongPtr(pFrameWindowSplitter->m_hwndparent, GWL_STYLE);
                SetWindowLongPtr(pFrameWindowSplitter->m_hwndparent, GWL_STYLE, pFrameWindowSplitter->m_prevstyle & ~WS_CLIPCHILDREN);
                pFrameWindowSplitter->m_hwndprevfocus = GetFocus();
                SetFocus(hwnd);
				SetCapture(hwnd);

				/*	starting from v4.2 BETA we stop the repaining of the two custom tab controls 
					so that flicker does not happen */
				pFrameWindowSplitter->m_isdragged	= wyTrue;
                pFrameWindowSplitter->MouseMove(wyTrue);
			}
		}
		break;
		
	case WM_LBUTTONUP:
		ReleaseCapture();
		break;

	case WM_CAPTURECHANGED:
		if(pFrameWindowSplitter->m_isdragged)
		{
            SetWindowLongPtr(pFrameWindowSplitter->m_hwndparent, GWL_STYLE, pFrameWindowSplitter->m_prevstyle);
            pFrameWindowSplitter->EndDrag(wyTrue);
			pFrameWindowSplitter->Resizeall();
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
			pFrameWindowSplitter->m_isdragged = wyFalse;

            if(pFrameWindowSplitter->m_hwndprevfocus)
            {
                SetFocus(pFrameWindowSplitter->m_hwndprevfocus);
                pFrameWindowSplitter->m_hwndprevfocus = NULL;
            }
		}
		break;
	}

	return(DefWindowProc(hwnd, message, wparam, lparam));
}