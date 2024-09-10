// 
//******************************************************************
//  Function Name : OnNcPaint
//  Function      : QA: 32574
//  Param         : HRGN hrgnUpdate
//  Return        : LRESULT 
//  Create        : 
//  Update        : ±èÁ¤¹®, 2009/10/09 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
LRESULT SECTreeCtrl::OnNcPaint(HRGN hrgnUpdate)
{
	if(!m_hTreeTheme)
	{
#ifndef __RWUXTHEME_H
		m_hTreeTheme = RWOpenThemeData(m_hWnd, L"TREEVIEW");
#endif
	}

	if(m_hTreeTheme)
	{
		//---------------------//
		// Draw Themed Border  //
		//---------------------//

		HDC hdc = ::GetWindowDC(m_hWnd);
		RECT rc;
		RECT rcWindow;
		DWORD state = ETS_NORMAL;
		HRGN hrgnClip;

		// State
		if(!::IsWindowEnabled(this->GetSafeHwnd()))
		{
			state = ETS_DISABLED;
		}else if(GetFocus() == this->GetParent())
		{
			state = ETS_HOT;
		}else
		{
			state = ETS_NORMAL;
		}

		// Rect mapping
		::GetWindowRect(m_hWnd, &rcWindow);
		::GetClientRect(m_hWnd, &rc);
		::ClientToScreen(m_hWnd, (POINT *)&rc.left);
		::ClientToScreen(m_hWnd, (POINT *)&rc.right);

		rc.right = rcWindow.right - (rc.left - rcWindow.left);
		rc.bottom = rcWindow.bottom - (rc.top - rcWindow.top);

		// Region
		hrgnClip = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if(hrgnUpdate != (HRGN)1)
		CombineRgn(hrgnClip, hrgnClip, hrgnUpdate, RGN_AND);

		OffsetRect(&rc, -rcWindow.left, -rcWindow.top);

		ExcludeClipRect(hdc, rc.left, rc.top, rc.right, rc.bottom);
		OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);

		//if (IsThemeBackgroundPartiallyTransparent (m_hTreeTheme, TVP_TREEITEM, state))
		//RWDrawThemeParentBackground(m_hWnd, hdc, &rcWindow);
#ifndef __RWUXTHEME_H
		RWDrawThemeBackground(m_hTreeTheme, hdc,
		TVP_TREEITEM, 
		state,
		&rcWindow, NULL);
#endif
		::ReleaseDC(m_hWnd, hdc);
	}

	return 0; 
}