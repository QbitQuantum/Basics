//--------------------------------------------------------------------------
//	功能：窗口函数（处理消息）
//--------------------------------------------------------------------------
int KWndEdit::WndProc(unsigned int uMsg, unsigned int uParam, int nParam)
{
	int	nRet = 0;
	if (m_Flag & WNDEDIT_ES_WIN32_WND)
	{
		if (uMsg == WM_KEYDOWN)
			nRet = OnKeyDownWin32(uParam, nParam);
		if (uMsg == WND_M_SET_FOCUS)
			Win32Edit_SetFocus(m_hWin32Wnd, true);
		else if (uMsg == WND_M_KILL_FOCUS)
			Win32Edit_SetFocus(m_hWin32Wnd, false);
		return 0;
	}

	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		if (IsVisible() && Wnd_GetFocusWnd() != (KWndWindow*)this)
		{
			Wnd_SetFocusWnd((KWndWindow*)this);
		}
		else
			nRet = KWndWindow::WndProc(uMsg, uParam, nParam);
		break;
	case WM_IME_CHAR:
	case WM_CHAR:
		if ((m_Flag & WNDEDIT_F_HAVE_FOCUS) && ((m_Style & WND_S_DISABLE) == 0))
		{
			if (InsertChar(uParam))
				UpdateData();
			nRet = 1;
		}
		break;
	case WM_KEYDOWN:
		if (!IsDisable())
			nRet = OnKeyDown(uParam, nParam);
		break;
	case WND_M_SET_FOCUS:
		if (m_pText)
		{
			if (m_Flag & WNDEDIT_ES_IME_AVAILABLE)
			{
				s_Ime.EnableLanguageChange();
				if (s_LastTimeIsIme)
				    s_Ime.OpenIME();
			}

//			m_nCaretPos = m_nTextLen;	//把光标位置设在文本末尾
			m_Flag |= WNDEDIT_F_HAVE_FOCUS;
			m_nCaretTime = 0;

//			CreateCaret(::g_GetMainHWnd(), (HBITMAP)NULL, 2, m_nFontSize);
            m_nCaretX = m_nAbsoluteLeft;
            m_nCaretY = m_nAbsoluteTop;
            SetCaretPos(m_nCaretX, m_nCaretY);
            s_Ime.SetCaretPos(m_nCaretX, m_nCaretY);

//          ShowCaret(::g_GetMainHWnd());
		}
		break;
	case WND_M_KILL_FOCUS:
//        DestroyCaret();

		if (m_Flag & WNDEDIT_ES_IME_AVAILABLE)
			s_LastTimeIsIme = s_Ime.IsIme();
		s_Ime.DisableLanguageChange();
		s_Ime.CloseIME();
		m_Flag &= ~WNDEDIT_F_HAVE_FOCUS;
		break;
	case WM_SYSKEYDOWN:
		if (m_pParentWnd)
			nRet = m_pParentWnd->WndProc(uMsg, uParam, nParam);
		break;
	case WM_MOUSEWHEEL:
		if (!IsDisable())
		{
			int zDelta = GET_Y_LPARAM(uParam);
			if (zDelta != 0)
				nRet = OnKeyDown(zDelta < 0 ? VK_DOWN : VK_UP, 0);
		}
		break;

    case WM_MOVING:
    case WM_MOVE:
    {
        if (m_Flag & WNDEDIT_ES_WIN32_WND)
        {
    	    Win32Edit_UpdateSizePos(m_hWin32Wnd, m_nAbsoluteLeft, m_nAbsoluteTop, m_Width, m_Height);
            break;
        }
    }
	default:
		nRet = KWndWindow::WndProc(uMsg, uParam, nParam);
		break;
	}
	return nRet;
}