void MenuEditorItem::PaintPopup(CDC& dc, CRect& rect)
{
	// draw this item

	dc.FillSolidRect(rect, 0xffffff);
	dc.Draw3dRect(rect,GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_BTNFACE));
	m_rect = rect;

	CRect temp = rect;
	
	if(pEditor->selected == this)
	{
		for(int x = temp.left; x < temp.right; x+=2)
		{
			dc.SetPixel(x,temp.top, 0);
			dc.SetPixel(x + 1- temp.Height()%2,temp.bottom-1, 0);
		}
		for(int y = temp.top; y < temp.bottom; y+=2)
		{
			dc.SetPixel(temp.left,y, 0);
			dc.SetPixel(temp.right-1,y +1- temp.Width()%2, 0);
		}
	}

	temp.DeflateRect(2,2);

	if(pEditor->selected == this)
		dc.FillSolidRect(temp, GetSysColor(COLOR_MENUHILIGHT));
	
	temp.left += 20;
	
	if(inserttext || m_Disabled)
		dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	else if(pEditor->selected == this)
		dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	else
		dc.SetTextColor(GetSysColor(COLOR_MENUTEXT));
	dc.DrawText(m_Text, temp, 0);

	//checkbox
	if(m_Checked)
	{
		COLORREF color = dc.GetTextColor();
		CRect drawzone = rect;
		drawzone.top += 8;
		drawzone.left += 5;
		drawzone.bottom = drawzone.top + 3;
		drawzone.right = drawzone.left + 1;
		for(int a = 0; a < 2;a++)
		{
			dc.FillSolidRect(drawzone, color);
			drawzone.OffsetRect(1,1);
		}
		for(int b = 0; b < 5;b++)
		{
			dc.FillSolidRect(drawzone, color);	
			drawzone.OffsetRect(1,-1);

		}

	}

	if (m_items.size() != 1 && m_items.size() != 0)
	{
		COLORREF color = dc.GetTextColor();
		CRect rect;
		rect = temp;
		rect.left = rect.right - 5;
		rect.right = rect.left + 1;
		rect.top += 4;
		rect.bottom -= 4;
		for(int a = 0; a < 4; a ++)
		{
			dc.FillSolidRect(rect, color);
			rect.top ++;
			rect.bottom --;
			rect.left ++;
			rect.right ++;
		}

	}

	///////////////////////

	rect.OffsetRect(0, rect.Height()+1);

}