void CControlResizer::DoReSize(int incrX, int incrY)
{
	INT_PTR arrayCount  = m_ResizePropArray.GetCount();
	CRgn updateRgn;
	updateRgn.CreateRectRgn(0, 0, 0, 0);
	bool bIsEmptyUpdateRgn(true);
	for (INT_PTR i = 0; i < arrayCount; i++) {
		const ResizeProp &rszProp(m_ResizePropArray.GetAt(i));
		if (IsHidden(rszProp.controlID)) continue;
		if (rszProp.uFlags & RSZF_NO_RESIZE) continue;
		RECT controlRect;
		CWnd *pControlWnd = m_pDialog->GetDlgItem(rszProp.controlID);
		pControlWnd->GetWindowRect(&controlRect);
		MapWindowPoints(NULL, m_pDialog->m_hWnd, (LPPOINT)&controlRect, 2);
		CRgn srcRgn;
		if (rszProp.uFlags & RSZF_RESIZE_UPDATE) {
			srcRgn.CreateRectRgn(controlRect.left, controlRect.top, controlRect.right, controlRect.bottom);
		}
		int widht = controlRect.right - controlRect.left;
		int height = controlRect.bottom - controlRect.top;
		int cx = incrX;
		int cy = incrY;
		if (rszProp.uFlags & RSZF_RESIZE_OPPOSITE) {
			cx = -cx;
			cy = -cy;
		}
		if (cx) {
			if (rszProp.uFlags & RSZF_SIZEX_FIXED) {
				OffsetRect(&controlRect, cx, 0);
			}
			else if (rszProp.uFlags & RSZF_RIGHT_FIXED) {
				controlRect.left = controlRect.right - widht - cx;
			}
			else if (rszProp.uFlags & RSZF_LEFT_FIXED) {
				controlRect.right = controlRect.left + widht + cx;
			}
		}
		if (cy) {
			if (rszProp.uFlags & RSZF_SIZEY_FIXED) {
				OffsetRect(&controlRect, 0, cy);
			}
			else if (rszProp.uFlags & RSZF_BOTTOM_FIXED) {
				controlRect.top = controlRect.bottom - height - cy;
			}
			else if (rszProp.uFlags & RSZF_TOP_FIXED) {
				controlRect.bottom = controlRect.top + height + cy;
			}
		}
		if (rszProp.uFlags & RSZF_RESIZE_UPDATE) {
			CRgn dst;
			dst.CreateRectRgn(controlRect.left, controlRect.top, controlRect.right, controlRect.bottom);
			updateRgn.CombineRgn(&srcRgn, &dst, RGN_OR);
			bIsEmptyUpdateRgn = false;
		}
		widht = controlRect.right - controlRect.left;
		height = controlRect.bottom - controlRect.top;
		pControlWnd->SetWindowPos(NULL, controlRect.left, controlRect.top, widht, height, SWP_NOZORDER);
	}
	if (!bIsEmptyUpdateRgn) {
		m_pDialog->InvalidateRgn(&updateRgn);
		m_pDialog->UpdateWindow();
	}
}