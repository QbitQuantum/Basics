LRESULT CJabberInfoFrame::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_APP:
		ReloadFonts();
		return 0;

	case WM_PAINT:
		{
			RECT rc; GetClientRect(m_hwnd, &rc);
			m_compact = rc.bottom < (2 * (GetSystemMetrics(SM_CYSMICON) + SZ_LINEPADDING) + SZ_LINESPACING + 2 * SZ_FRAMEPADDING);

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_hwnd, &ps);
			m_compact ? PaintCompact(hdc) : PaintNormal(hdc);
			EndPaint(m_hwnd, &ps);
			return 0;
		}

	case WM_RBUTTONUP:
		{
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			MapWindowPoints(m_hwnd, NULL, &pt, 1);
			HMENU hMenu = (HMENU)CallService(MS_CLIST_MENUBUILDFRAMECONTEXT, m_frameId, 0);
			int res = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, 0, pcli->hwndContactList, NULL);
			CallService(MS_CLIST_MENUPROCESSCOMMAND, MAKEWPARAM(res, 0), m_frameId);
			return 0;
		}

	case WM_LBUTTONDOWN:
		{
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			for (int i=0; i < m_pItems.getCount(); i++)
				if (m_pItems[i].m_onEvent && PtInRect(&m_pItems[i].m_rcItem, pt)) {
					m_clickedItem = i;
					return 0;
				}
		}
		return 0;

	case WM_LBUTTONUP:
		{
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			if ((m_clickedItem >= 0) && (m_clickedItem < m_pItems.getCount()) && m_pItems[m_clickedItem].m_onEvent && PtInRect(&m_pItems[m_clickedItem].m_rcItem, pt))
			{
				CJabberInfoFrame_Event evt;
				evt.m_event = CJabberInfoFrame_Event::CLICK;
				evt.m_pszName = m_pItems[m_clickedItem].m_pszName;
				evt.m_pUserData = m_pItems[m_clickedItem].m_pUserData;
				(m_proto->*m_pItems[m_clickedItem].m_onEvent)(&evt);
				return 0;
			}

			m_clickedItem = -1;

			return 0;
		}

	case WM_LBUTTONDBLCLK:
		m_compact = !m_compact;
		UpdateSize();
		return 0;
	}

	return DefWindowProc(m_hwnd, msg, wParam, lParam);
}