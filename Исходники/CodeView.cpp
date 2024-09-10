void CCodeView::OnPaint(wxPaintEvent& event)
{
	// --------------------------------------------------------------------
	// General settings
	// -------------------------
	wxPaintDC dc(this);
	wxRect rc = GetClientRect();

	dc.SetFont(DebuggerFont);

	wxCoord w,h;
	dc.GetTextExtent("0WJyq", &w, &h);

	if (h > m_rowHeight)
		m_rowHeight = h;

	dc.GetTextExtent("W", &w, &h);
	int charWidth = w;

	struct branch
	{
		int src, dst, srcAddr;
	};

	branch branches[256];
	int numBranches = 0;
	// TODO: Add any drawing code here...
	int width   = rc.width;
	int numRows = (rc.height / m_rowHeight) / 2 + 2;
	// ------------

	// --------------------------------------------------------------------
	// Colors and brushes
	// -------------------------
	dc.SetBackgroundMode(wxTRANSPARENT); // the text background
	const wxColour bgColor = *wxWHITE;
	wxPen nullPen(bgColor);
	wxPen currentPen(*wxBLACK_PEN);
	wxPen selPen(*wxGREY_PEN);
	nullPen.SetStyle(wxTRANSPARENT);
	currentPen.SetStyle(wxSOLID);
	wxBrush currentBrush(*wxLIGHT_GREY_BRUSH);
	wxBrush pcBrush(*wxGREEN_BRUSH);
	wxBrush bpBrush(*wxRED_BRUSH);

	wxBrush bgBrush(bgColor);
	wxBrush nullBrush(bgColor);
	nullBrush.SetStyle(wxTRANSPARENT);

	dc.SetPen(nullPen);
	dc.SetBrush(bgBrush);
	dc.DrawRectangle(0, 0, 16, rc.height);
	dc.DrawRectangle(0, 0, rc.width, 5);
	// ------------

	// --------------------------------------------------------------------
	// Walk through all visible rows
	// -------------------------
	for (int i = -numRows; i <= numRows; i++)
	{
		unsigned int address = m_curAddress + i * m_align;

		int rowY1 = rc.height / 2 + m_rowHeight * i - m_rowHeight / 2;
		int rowY2 = rc.height / 2 + m_rowHeight * i + m_rowHeight / 2;

		wxString temp = wxString::Format("%08x", address);
		u32 col = m_debugger->GetColor(address);
		wxBrush rowBrush(wxColour(col >> 16, col >> 8, col));
		dc.SetBrush(nullBrush);
		dc.SetPen(nullPen);
		dc.DrawRectangle(0, rowY1, 16, rowY2 - rowY1 + 2);

		if (m_selecting && (address == m_selection))
			dc.SetPen(selPen);
		else
			dc.SetPen(i == 0 ? currentPen : nullPen);

		if (address == m_debugger->GetPC())
			dc.SetBrush(pcBrush);
		else
			dc.SetBrush(rowBrush);

		dc.DrawRectangle(16, rowY1, width, rowY2 - rowY1 + 1);
		dc.SetBrush(currentBrush);
		if (!m_plain)
		{
			dc.SetTextForeground("#600000"); // the address text is dark red
			dc.DrawText(temp, 17, rowY1);
			dc.SetTextForeground(*wxBLACK);
		}

		// If running
		if (m_debugger->IsAlive())
		{
			char dis[256];
			m_debugger->Disassemble(address, dis, 256);
			char* dis2 = strchr(dis, '\t');
			char desc[256] = "";

			// If we have a code
			if (dis2)
			{
				*dis2 = 0;
				dis2++;
				// look for hex strings to decode branches
				const char* mojs = strstr(dis2, "0x8");
				if (mojs)
				{
					for (int k = 0; k < 8; k++)
					{
						bool found = false;
						for (int j = 0; j < 22; j++)
						{
							if (mojs[k + 2] == "0123456789ABCDEFabcdef"[j])
								found = true;
						}
						if (!found)
						{
							mojs = nullptr;
							break;
						}
					}
				}
				if (mojs)
				{
					int offs;
					sscanf(mojs + 2, "%08x", &offs);
					branches[numBranches].src = rowY1 + m_rowHeight / 2;
					branches[numBranches].srcAddr = address / m_align;
					branches[numBranches++].dst = (int)(rowY1 + ((s64)(u32)offs - (s64)(u32)address) * m_rowHeight / m_align + m_rowHeight / 2);
					sprintf(desc, "-->%s", m_debugger->GetDescription(offs).c_str());
					dc.SetTextForeground(wxTheColourDatabase->Find("PURPLE")); // the -> arrow illustrations are purple
				}
				else
				{
					dc.SetTextForeground(*wxBLACK);
				}

				dc.DrawText(StrToWxStr(dis2), 17 + 17*charWidth, rowY1);
				// ------------
			}

			// Show blr as its' own color
			if (strcmp(dis, "blr"))
				dc.SetTextForeground(wxTheColourDatabase->Find("DARK GREEN"));
			else
				dc.SetTextForeground(wxTheColourDatabase->Find("VIOLET"));

			dc.DrawText(StrToWxStr(dis), 17 + (m_plain ? 1*charWidth : 9*charWidth), rowY1);

			if (desc[0] == 0)
			{
				strcpy(desc, m_debugger->GetDescription(address).c_str());
			}

			if (!m_plain)
			{
				dc.SetTextForeground(*wxBLUE);

				//char temp[256];
				//UnDecorateSymbolName(desc,temp,255,UNDNAME_COMPLETE);
				if (strlen(desc))
				{
					dc.DrawText(StrToWxStr(desc), 17 + 35 * charWidth, rowY1);
				}
			}

			// Show red breakpoint dot
			if (m_debugger->IsBreakpoint(address))
			{
				dc.SetBrush(bpBrush);
				dc.DrawRectangle(2, rowY1 + 1, 11, 11);
			}
		}
	} // end of for
	// ------------

	// --------------------------------------------------------------------
	// Colors and brushes
	// -------------------------
	dc.SetPen(currentPen);

	for (int i = 0; i < numBranches; i++)
	{
		int x = 17 + 49 * charWidth + (branches[i].srcAddr % 9) * 8;
		MoveTo(x-2, branches[i].src);

		if (branches[i].dst < rc.height + 400 && branches[i].dst > -400)
		{
			LineTo(dc, x+2, branches[i].src);
			LineTo(dc, x+2, branches[i].dst);
			LineTo(dc, x-4, branches[i].dst);

			MoveTo(x, branches[i].dst - 4);
			LineTo(dc, x-4, branches[i].dst);
			LineTo(dc, x+1, branches[i].dst+5);
		}
		//else
		//{
			// This can be re-enabled when there is a scrollbar or
			// something on the codeview (the lines are too long)

			//LineTo(dc, x+4, branches[i].src);
			//MoveTo(x+2, branches[i].dst-4);
			//LineTo(dc, x+6, branches[i].dst);
			//LineTo(dc, x+1, branches[i].dst+5);
		//}

		//LineTo(dc, x, branches[i].dst+4);
		//LineTo(dc, x-2, branches[i].dst);
	}
	// ------------
}