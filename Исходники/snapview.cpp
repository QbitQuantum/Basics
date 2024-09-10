void CSnapView::OnSize(UINT nType, int cx, int cy)
{
	if (nType != SIZE_MINIMIZED && cx != 0 && cy != 0 && m_pPropSheet != NULL)
	{
		if (m_bSizedBefore == FALSE)
		{
			m_bSizedBefore = TRUE;

			// get the size of the property sheet
			CRect rectSized;
			m_pPropSheet->GetWindowRect(rectSized);

			// calculate the size of the frame
			CFrameWnd* pFrame = GetParentFrame();
			if (pFrame != NULL)
			{
				pFrame->CalcWindowRect(rectSized);
				CWnd* pParent = pFrame->GetParent();

				if (pParent != NULL)
					pParent->ScreenToClient(rectSized);

				// resize and reposition the frame
				pFrame->MoveWindow(rectSized);
			}
		}
	}
}