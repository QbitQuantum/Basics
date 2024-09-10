void XGPopMenuView::DrawLine(XGDraw &draw, short line, bool hilite)
{
	XRect r;
	int h;
	char item[256];
	char *iptr;
	bool enable;
	short t,b;
	
	/*
	 *	Verify that I'm drawing in range
	 */
	
	if (fScroll == 0) {
		t = 0;
	} else {
		t = fScroll+1;
	}
	
	if (fScroll < fMaxScroll) {
		b = fHeight + fScroll - 1;
	} else {
		b = fList->GetNumStrings();
	}
	
	if ((line < t) || (line >= b)) return;
	
	/*
	 *	Find where I'm drawing
	 */

	r = GetContentRect();
	::InsetRect(&r,3,3);
	h = draw.GetFontHeight();
	r.top = (line - fScroll) * h + 3;
	r.bottom = r.top + h;
	
	h = r.bottom - 1 - draw.GetFontDescent();
	
	/*
	 *	Draw the dsabled text line (if the line is disabled)
	 */

	fList->GetString(line,item);
	if (item[0] == 0) {
		XRect s;
		
		/*
		 *	Separator
		 */
		
		draw.Draw3DRect(r,KXGEBackground);
		s = r;
		s.top = (r.top + r.bottom) / 2;
		s.bottom = s.top + 1;
		draw.FillRect(s,KXGColorBtnShadow);
		s.top++;
		s.bottom++;
		draw.FillRect(s,KXGColorBtnHilite);
		return;
	}
		
	/*
	 *	Draw the hilite
	 */
	
	iptr = item;
	if (*iptr == 0x02) {
		enable = false;
		iptr++;
	} else {
		enable = true;
	}
	if (enable) {
		if (hilite) {
			draw.FillRect(r,KXGColorMHilite);
			draw.SetForeColor(KXGColorMHiliteText);
		} else {
			draw.SetForeColor(KXGColorBlack);
			draw.Draw3DRect(r,KXGEBackground);
		}
	} else {
		draw.SetForeColor(KXGColorBtnShadow);		// disabled text
		draw.Draw3DRect(r,KXGEBackground);
	}
		
	/*
	 *	Draw the line
	 */
	
	if (*iptr == 0x01) {
		XRect s;
		
		iptr++;
		s.top = r.top + 2;
		s.left = 5;
		s.bottom = h;
		s.right = s.left + (s.bottom - s.top);
		draw.PaintOval(s);
	}
	draw.MoveTo(20,h);
	draw.DrawString(iptr);
}