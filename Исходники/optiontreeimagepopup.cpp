void COptionTreeImagePopUp::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// Declare variables
	BOOL bFound = FALSE;
	CRect rcImage;
	CRect rcClient;

	// Get client rect
	GetClientRect(rcClient);

	// See if user clicked outside window
	if (rcClient.PtInRect(point) == FALSE)
	{
		// ALWAYS send message to parent
		if (IsWindow(m_pParent->GetSafeHwnd()))
		{
			m_pParent->SendMessage(OT_IMAGE_CLOSE, 0, m_nSelected);
		}

		ReleaseCapture();
		DestroyWindow();
		return;
	}

	// Go through all images
	for (int i = 0; i < m_pImageList->GetImageCount(); i++)
	{
		// -- Get rectangle
		rcImage = m_rcRectangles.GetAt(i);

		// -- See if selected
		if (m_nSelected == i)
		{
			rcImage.InflateRect(3, 3, 3, 3);
		}

		// -- Hit test
		if (rcImage.PtInRect(point) == TRUE)
		{
			// -- -- Select this image
			m_nSelected = i;

			// -- -- Found
			bFound = TRUE;

			break;
		}
	}

	// Close
	if (bFound == TRUE)
	{
		// ALWAYS send message to parent
		if (IsWindow(m_pParent->GetSafeHwnd()))
		{
			m_pParent->SendMessage(OT_IMAGE_CLOSE, 0, m_nSelected);
		}

		ReleaseCapture();
		DestroyWindow();
		return;
	}


	// Handle left click
	CWnd::OnLButtonUp(nFlags, point);
}