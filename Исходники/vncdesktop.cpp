// Add the mouse pointer to the buffer
void
vncDesktop::CaptureMouse(BYTE *scrBuff, UINT scrBuffSize)
{
	POINT CursorPos;
	ICONINFO IconInfo;

	// If the mouse cursor handle is invalid then forget it
	if (m_hcursor == NULL)
		return;

	// Get the cursor position
	if (!GetCursorPos(&CursorPos))
		return;

	// Translate position for hotspot
	if (GetIconInfo(m_hcursor, &IconInfo))
	{
		CursorPos.x -= ((int) IconInfo.xHotspot);
		CursorPos.y -= ((int) IconInfo.yHotspot);
		if (IconInfo.hbmMask != NULL)
			DeleteObject(IconInfo.hbmMask);
		if (IconInfo.hbmColor != NULL)
			DeleteObject(IconInfo.hbmColor);
	}

	// Select the memory bitmap into the memory DC
	HBITMAP oldbitmap;
	if ((oldbitmap = (HBITMAP) SelectObject(m_hmemdc, m_membitmap)) == NULL)
		return;

	// Draw the cursor
	DrawIconEx(
		m_hmemdc,									// handle to device context 
		CursorPos.x, CursorPos.y,
		m_hcursor,									// handle to icon to draw 
		0,0,										// width of the icon 
		0,											// index of frame in animated cursor 
		NULL,										// handle to background brush 
		DI_NORMAL | DI_COMPAT						// icon-drawing flags 
		);

	// Select the old bitmap back into the memory DC
	SelectObject(m_hmemdc, oldbitmap);

	// Save the bounding rectangle
	m_cursorpos.tl = CursorPos;
	m_cursorpos.br = rfb::Point(GetSystemMetrics(SM_CXCURSOR),
		GetSystemMetrics(SM_CYCURSOR)).translate(CursorPos);

	// Clip the bounding rect to the screen
	// Copy the mouse cursor into the screen buffer, if any of it is visible
	m_cursorpos = m_cursorpos.intersect(m_bmrect);
	if (!m_cursorpos.is_empty()) {
		CopyToBuffer(m_cursorpos, scrBuff, scrBuffSize);
	}
}