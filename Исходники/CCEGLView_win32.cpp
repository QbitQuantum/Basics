LRESULT CCEGLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		if (m_pDelegate && m_pTouch && MK_LBUTTON == wParam)
		{
            POINT pt = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            if (PtInRect(&m_rcViewPort, pt))
            {
                m_bCaptured = true;
                SetCapture(m_hWnd);
                m_pTouch->SetTouchInfo((float)(pt.x - m_rcViewPort.left) / m_fScreenScaleFactor,
                    (float)(pt.y - m_rcViewPort.top) / m_fScreenScaleFactor);
                m_pSet->addObject(m_pTouch);
                m_pDelegate->touchesBegan(m_pSet, NULL);
            }
		}
		break;

	case WM_MOUSEMOVE:
		if (MK_LBUTTON == wParam && m_bCaptured)
		{
            m_pTouch->SetTouchInfo((float)((short)LOWORD(lParam)- m_rcViewPort.left) / m_fScreenScaleFactor,
                (float)((short)HIWORD(lParam) - m_rcViewPort.top) / m_fScreenScaleFactor);
            m_pDelegate->touchesMoved(m_pSet, NULL);
		}
		break;

	case WM_LBUTTONUP:
		if (m_bCaptured)
		{
			m_pTouch->SetTouchInfo((float)((short)LOWORD(lParam)- m_rcViewPort.left) / m_fScreenScaleFactor,
                (float)((short)HIWORD(lParam) - m_rcViewPort.top) / m_fScreenScaleFactor);
			m_pDelegate->touchesEnded(m_pSet, NULL);
			m_pSet->removeObject(m_pTouch);
            ReleaseCapture();
			m_bCaptured = false;
		}
		break;
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_RESTORED:
			CCApplication::sharedApplication().applicationWillEnterForeground();
			break;
		case SIZE_MINIMIZED:
			CCApplication::sharedApplication().applicationDidEnterBackground();
			break;
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_F1 || wParam == VK_F2)
		{
			if (GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
				CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(wParam == VK_F1 ? kTypeBackClicked : kTypeMenuClicked, 1);
		}
		else if ((wParam >= 'A' && wParam <= 'Z') || (wParam >= 'a' && wParam <= 'z'))
		{
			CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(wParam, 1);
		}

		if ( m_lpfnAccelerometerKeyHook!=NULL )
		{
			(*m_lpfnAccelerometerKeyHook)( message,wParam,lParam );
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_F1 || wParam == VK_F2)
		{
			if (GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
				CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(wParam == VK_F1 ? kTypeBackClicked : kTypeMenuClicked, 0);
		}
		else if ((wParam >= 'A' && wParam <= 'Z') || (wParam >= 'a' && wParam <= 'z'))
		{
			CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(wParam, 0);
		}

		if ( m_lpfnAccelerometerKeyHook!=NULL )
		{
			(*m_lpfnAccelerometerKeyHook)( message,wParam,lParam );
		}
		break;
    case WM_CHAR:
        {
            if (wParam < 0x20)
            {
                if (VK_BACK == wParam)
                {
                    CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
                }
                else if (VK_RETURN == wParam)
                {
                    CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
                }
                else if (VK_TAB == wParam)
                {
                    // tab input
                }
                else if (VK_ESCAPE == wParam)
                {
                    // ESC input
					CCDirector::sharedDirector()->end();
                }
            }
            else if (wParam < 128)
            {
                // ascii char
                CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&wParam, 1);
            }
            else
            {
                char szUtf8[8] = {0};
                int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)&wParam, 1, szUtf8, sizeof(szUtf8), NULL, NULL);

                CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
            }
			if ( m_lpfnAccelerometerKeyHook!=NULL )
			{
				(*m_lpfnAccelerometerKeyHook)( message,wParam,lParam );
			}
        }
        break;

	case WM_PAINT:
		BeginPaint(m_hWnd, &ps);
		EndPaint(m_hWnd, &ps);
		break;

	case WM_CLOSE:
		CCDirector::sharedDirector()->end();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}
	return 0;
}