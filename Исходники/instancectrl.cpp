void GroupVisual::Draw ( wxDC& dc, InstanceCtrl* parent, wxRect limitingRect, bool hasSelection, int selectionIndex, bool hasFocus, int focusIndex, bool highlight )
{
	int i;
	int count = items.size();
	int style = 0;
	wxRect rect;
	
	// Draw the header
	if(!no_header)
	{
		wxColour textColor = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);

		if (highlight)
		{
			textColor = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
		}

		wxBrush brush(textColor);
		wxPen pen(textColor);
		dc.SetBrush(brush);
		dc.SetPen(pen);
		wxSize sz = dc.GetTextExtent(GetName());
		dc.SetTextForeground(textColor);
		
		dc.DrawText( GetName() , 20, y_position + 5 );
		int atheight = y_position + header_height / 2;
		if(sz.x + 30 < limitingRect.width - 10)
			dc.DrawLine(sz.x + 30,atheight, limitingRect.width - 10, atheight);
		
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.SetPen(textColor);
		
		// Ungrouped can't be hidden, so don't draw the box.
		if (m_group)
		{
			dc.DrawRectangle(5,atheight -5, 10,10);
			dc.DrawRectangle(7,atheight -1, 6,2);
			if(!IsExpanded())
			{
				dc.DrawRectangle(9,atheight -3, 2,6);
			}
		}
	}
	
	if(IsExpanded()) for (i = 0; i < count; i++)
	{
		parent->GetItemRect(VisualCoord(index,i), rect, false);

		if (!limitingRect.Intersects(rect))
			continue;
		style = 0;
		if (hasSelection && selectionIndex == i)
			style |= wxINST_SELECTED;
		if (hasFocus && i == focusIndex)
			style |= wxINST_IS_FOCUS;

		InstanceVisual& item = items[i];
		item.Draw(dc, parent, rect, style);
	}
}