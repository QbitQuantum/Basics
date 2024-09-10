void WeightTableWindow::PaintCellAttribute(HDC hdc, int x, int y, BOOL sel, int state)
	{
	HBRUSH textBackground;
	DWORD textColor;
	DWORD textBKColor;
	SIZE strSize;

	if (sel)
		{
		
		textBackground = GetSysColorBrush(COLOR_HIGHLIGHT);
		textColor = GetSysColor(COLOR_HIGHLIGHTTEXT) ;
		textBKColor = GetSysColor(COLOR_HIGHLIGHT) ;
		SelectObject(hdc, hFixedFontBold);
 		}
	else
		{
		textBackground = ColorMan()->GetBrush(kWindow );
		textColor = ColorMan()->GetColor(kWindowText ) ;
		textBKColor = ColorMan()->GetColor(kWindow ) ;
		SelectObject(hdc, hFixedFont);
		}
	SetTextColor(hdc, textColor);
	SelectObject(hdc, textBackground);
	SetBkColor(hdc,  textBKColor);
	SelectObject(hdc,pBackPen);

	TSTR stateStr;
	if (state == STATE_CHECKED)
		stateStr.printf("X");
	else if (state == STATE_INDETERMIANT)
		stateStr.printf("-");
	else stateStr.printf(" ");

	int offset;
	GetTextExtentPoint32(hdc, (LPCTSTR) stateStr, stateStr.Length(), (LPSIZE) &strSize ); 
	if (GetFlipFlopUI())
		offset = vertNameWidth/2 - strSize.cx/2;
	else offset = textHeight/2 - strSize.cx/2;
	if (GetFlipFlopUI())
		Rectangle(hdc, x,  y,x+vertNameWidth+1,y+textHeight+1);
	else Rectangle(hdc, x,  y,x+textHeight+1,y+textHeight+1);

	TextOut(hdc, x+offset,y+1,stateStr,stateStr.Length());

	}