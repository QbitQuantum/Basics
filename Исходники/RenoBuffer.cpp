VOID CRenoBuffer::OnPaint()
{
	CPaintDC dc(this);

	CRect clipRect;
	dc.GetClipBox(clipRect);

	CRect clientRect;
	GetClientRect(clientRect);

	// Start doublebuffering
	HDC hCompatibleDC = CreateCompatibleDC(dc.GetSafeHdc());
	HBITMAP hBackbuffer = CreateCompatibleBitmap(dc.GetSafeHdc(),clientRect.Width(),clientRect.Height());
	HBITMAP hOldBitmap  = (HBITMAP)SelectObject(hCompatibleDC,hBackbuffer);

	SetBoundsRect(hCompatibleDC,clipRect,NULL);

	FillRect(hCompatibleDC,clientRect,(HBRUSH)CBrush(BACKGROUND_COLOR).GetSafeHandle());

	HGDIOBJ hOldFont = SelectObject(hCompatibleDC,theApp.GetFont());
	SetBkMode(hCompatibleDC,TRANSPARENT);

	CRect boundsRect;
	GetClientRect(boundsRect);
	boundsRect.DeflateRect(RENO_BUFFER_MARGIN_HORIZONTAL,RENO_BUFFER_MARGIN_VERTICAL);

	COLORREF colorDefault = GetTextColor(hCompatibleDC);
	COLORREF colorSystem = RGB(44,88,222);

	SIZE size;
	TEXTMETRIC textmetrics;

	for(LONG i = m_BufferScrollLine; i < m_Buffer.GetCount(); ++i)
	{
		if(!m_Buffer[i].GetLength())
		{
			GetTextExtentPoint32(hCompatibleDC,TEXT(" "),1,&size);
			boundsRect.bottom -= size.cy;
			continue;
		}

		// Currently only color system messages
		if(m_Buffer[i].GetAt(0) == TEXT('*'))
			SetTextColor(hCompatibleDC,colorSystem);
		else
			SetTextColor(hCompatibleDC,colorDefault);

		// Set a fixed stack size
		ULONG stack[32];
		ULONG stackTop = 0;

		// Put the default font at the bottom of the stack
		stack[stackTop++] = RENO_FONT_NORMAL;

		LONG x = boundsRect.left;
		LONG index = 0;

		while(index < m_Buffer[i].GetLength())
		{
			LONG control = -1;

			// Find a control character
			for(LONG j = index + 1; j < m_Buffer[i].GetLength(); ++j)
			{
				if(m_Buffer[i].GetAt(j) == IRC_CONTROL_BOLD || 
					m_Buffer[i].GetAt(j) == IRC_CONTROL_UNDERLINE || 
					m_Buffer[i].GetAt(j) == IRC_CONTROL_ITALIC || 
					m_Buffer[i].GetAt(j) == IRC_CONTROL_NORMAL)
				{
					// Found one
					control = j;
					break;
				}
			}

			if(control == -1)
			{
				// We are going to the end of the line
				control = m_Buffer[i].GetLength();
			}

			// Colors

			// "black"			: "\x0301",
			// "dark blue"		: "\x0302",
			// "dark green"		: "\x0303",
			// "green"			: "\x0303",
			// "red"			: "\x0304",
			// "light red"		: "\x0304",
			// "dark red"		: "\x0305",
			// "purple"			: "\x0306",
			// "brown"			: "\x0307",	// On some clients this is orange, others it is brown
			// "orange"			: "\x0307",
			// "yellow"			: "\x0308",
			// "light green"	: "\x0309",
			// "aqua"			: "\x0310",
			// "light blue"		: "\x0311",
			// "blue"			: "\x0312",
			// "violet"			: "\x0313",
			// "grey"			: "\x0314",
			// "gray"			: "\x0314",
			// "light grey"		: "\x0315",
			// "light gray"		: "\x0315",
			// "white"			: "\x0316",

			// Other formatting

			// "normal"			: "\x0F",
			// "bold"			: "\x02",
			// "reverse"		: "\x16",
			// "underline"		: "\x1F",

			switch(m_Buffer[i].GetAt(index))
			{
			case IRC_CONTROL_BOLD:
				if(stack[stackTop-1] == RENO_FONT_BOLD)
					--stackTop;	// Pop the top
				else
					stack[stackTop++] = RENO_FONT_BOLD;	// Push

				++index;	// Skip the control character
				break;

			case IRC_CONTROL_ITALIC:
				if(stack[stackTop-1] ==RENO_FONT_ITALIC)
					--stackTop;	// Pop the top
				else
					stack[stackTop++] = RENO_FONT_ITALIC;	// Push

				++index;	// Skip the control character
				break;

			case IRC_CONTROL_UNDERLINE:
				if(stack[stackTop-1] == RENO_FONT_UNDERLINE)
					--stackTop;	// Pop the top
				else
					stack[stackTop++] = RENO_FONT_UNDERLINE;	// Push

				++index;	// Skip the control character
				break;

			case IRC_CONTROL_NORMAL:
				if(stack[stackTop-1] == RENO_FONT_NORMAL && stackTop > 1)
					--stackTop;	// Pop the top
				else
					stack[stackTop++] = RENO_FONT_NORMAL;	// Push

				++index;	// Skip the control character
				break;
			}

			if(control - index)
			{
				SelectObject(hCompatibleDC,theApp.GetFont(stack[stackTop-1]));

				GetTextExtentPoint32(hCompatibleDC,m_Buffer[i].GetBuffer() + index,control - index,&size);

				TextOut(hCompatibleDC,x,boundsRect.bottom - size.cy,m_Buffer[i].GetBuffer() + index,control - index);
				
				x += size.cx;

				// Retrieve the overhang value from the TEXTMETRIC structure and subtract it from the x-increment (This is only necessary for non-TrueType raster fonts)
				GetTextMetrics(hCompatibleDC,&textmetrics);
				x -= textmetrics.tmOverhang;
			}

			index = control;
		}

		GetTextExtentPoint32(hCompatibleDC,TEXT(" "),1,&size);	// TODO Maybe not necessary, the size struct will already be set from some above call
		boundsRect.bottom -= size.cy;

		if(boundsRect.bottom < -size.cy)
			break;	// No point in painting further cause everything would get clipped
	}

	// Update the scrollbar
	if(m_Buffer.GetCount() > 1)
	{
		SelectObject(hCompatibleDC,theApp.GetFont());
		GetTextMetrics(hCompatibleDC,&textmetrics);

		SCROLLINFO info;
		info.cbSize = sizeof(info);

		info.fMask = SIF_ALL;
		info.nMin = 0;
		info.nMax = m_Buffer.GetCount()-1 + clientRect.Height()/textmetrics.tmHeight-1;
		info.nPos = m_Buffer.GetCount()-1 - m_BufferScrollLine;
		info.nPage = clientRect.Height()/textmetrics.tmHeight;

		SetScrollInfo(SB_VERT,&info);
		EnableScrollBar(SB_VERT,ESB_ENABLE_BOTH);
	}
	else
	{
		EnableScrollBar(SB_VERT,ESB_DISABLE_BOTH);
	}

	SelectObject(hCompatibleDC,hOldFont);

	// End doublebuffering
	BitBlt(dc.GetSafeHdc(),0,0,clientRect.Width(),clientRect.Height(),hCompatibleDC,0,0,SRCCOPY);
	SelectObject(hCompatibleDC,hOldBitmap);
	DeleteObject(hBackbuffer);
	DeleteDC(hCompatibleDC);
}