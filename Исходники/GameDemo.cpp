	void DoPaint()
	{
		RECT rcClient = { 0 };
		::GetClientRect(m_hWnd, &rcClient);
		DWORD dwWidth = rcClient.right - rcClient.left;
		DWORD dwHeight = rcClient.bottom - rcClient.top;

		HDC hDcPaint = ::GetDC(m_hWnd);
		HDC hDcBackground = ::CreateCompatibleDC(hDcPaint);
		COLORREF* pBackgroundBits;
		HBITMAP hbmpBackground = CreateMyBitmap(hDcPaint, dwWidth, dwHeight, &pBackgroundBits);
		::ZeroMemory(pBackgroundBits, dwWidth * dwHeight * 4);
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hDcBackground, hbmpBackground);
		SetBkMode(hDcBackground, OPAQUE);
		m_pm.GetRoot()->SetPos(rcClient);
		m_pm.GetRoot()->DoPaint(hDcBackground, rcClient);
		
		PaintArrow(hDcBackground, rcClient);
		ResetAlpha((BYTE*)pBackgroundBits, dwWidth, dwHeight);

		RECT rcWnd = { 0 };
		::GetWindowRect(m_hWnd, &rcWnd);

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		POINT ptPos = { rcWnd.left, rcWnd.top };
		SIZE sizeWnd = { dwWidth, dwHeight };
		POINT ptSrc = { 0, 0 };
		UpdateLayeredWindow(m_hWnd, hDcPaint, &ptPos, &sizeWnd, hDcBackground, &ptSrc, 0, &bf, ULW_ALPHA);

		::SelectObject(hDcBackground, hOldBitmap);
		if (hDcBackground != NULL) ::DeleteDC(hDcBackground);
		if (hbmpBackground != NULL) ::DeleteObject(hbmpBackground);
		::ReleaseDC(m_hWnd, hDcPaint);
	}