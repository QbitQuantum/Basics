/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the cells text on the left hand side using 
	the CUGCellType::DrawText function, so that all
	standard text drawing capabilities are available.
	Draws the sort arrows on the right according to
	their current pressed/raised state.

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGSpinButtonType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							  CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
			m_useThemes = cell->UseThemes();
	
	int style = 0;
	if( cell->IsPropertySet( UGCELL_CELLTYPEEX_SET ) )
		style = cell->GetCellTypeEx();

	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	//if the cell is not current and hide button is on
	//then dont draw the button
	if( style & UGCT_SPINBUTTONHIDEBUTTON && !current)
	{
		CUGCellType::OnDraw(dc,rect,col,row,cell,selected,current);
		return;
	}

	DrawBorder(dc,rect,rect,cell);

	int t,x,y;
	RECT rectout;
	CPen * oldpen;
	int left = rect->left;
	int height = rect->bottom - rect->top;

#ifdef UG_ENABLE_PRINTING
	if (dc->IsPrinting())
	{
		rect->left += (int) fScale;
		rect->right -= (int) fScale;
		rect->top += (int) fScale;
		rect->bottom -= (int) fScale;
	}
#endif

	rect->left = rect->right - (int) (fScale * btnWidth);
	
	// The Spin type does not contain themes we can use for selected or current, we use the same for both.
	UGXPThemeState topstate = UGXPThemes::GetState(selected > 0 || current > 0, false);

	//draw the top button
	t = rect->bottom;
	rect->bottom = rect->top + (rect->bottom - rect->top) / 2;
	if(btnTopDown && current){
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
		topstate = ThemeStatePressed;
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeSpinUp, topstate, &rectout, NULL))
	{
		//fill the border in
		dc->SetBkColor(GetSysColor(COLOR_BTNFACE));
		dc->FillRect(&rectout,&brush);

		//draw the down arrow
		if( height >9 ){
			if( dc->IsPrinting() )
			{
	#ifdef UG_ENABLE_PRINTING
				CRgn rgn;

				int	nWidth = rectout.right - rectout.left;
				int	nHeight = rectout.bottom - rectout.top;

				POINT point[] = {
					{rectout.left + nWidth / 2, rectout.top + nHeight / 2 - (int) fScale} ,
					{rectout.left + nWidth / 2 - (int) (2 * fScale), rectout.top + nHeight / 2 + (int) fScale} ,
					{rectout.left + nWidth / 2 + (int) (2 * fScale), rectout.top + nHeight / 2 + (int) fScale}
				};

				rgn.CreatePolygonRgn(point, 3, ALTERNATE);

				CBrush Brush;
				Brush.CreateSolidBrush(RGB(0, 0 , 0));
				dc->FillRgn(&rgn, &Brush);
	#endif
			}
			else {
				x = ((btnWidth-5)/2) + rect->left;
				y = ((rect->bottom - rect->top -3)/2) + rect->top;
				dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
				dc->MoveTo(x,y+2);
				dc->LineTo(x+5,y+2);
				dc->MoveTo(x+1,y+1);
				dc->LineTo(x+4,y+1);
				dc->MoveTo(x+2,y);
				dc->LineTo(x+2,y+1);
			}
		}
	}

	//reset the rect
	rect->bottom = t;

	// The Spin type does not contain themes we can use for selected or current, we use the same for both.
	UGXPThemeState bottomstate = UGXPThemes::GetState(selected > 0 || current > 0, false);

	//draw the bottom button
	t = rect->top;
	rect->top = (rect->top +(rect->bottom - rect->top)/2);
	if(btnBottomDown && current){
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
		bottomstate = ThemeStatePressed;
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}
	//fill the border in
	dc->SetBkColor(GetSysColor(COLOR_BTNFACE));
	dc->FillRect(&rectout,&brush);

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeSpinDown, bottomstate, &rectout, NULL))
	{
		//draw the down arrow
		if(height >9){
			if( dc->IsPrinting() )
			{
	#ifdef UG_ENABLE_PRINTING
				CRgn rgn;

				int	nWidth = rectout.right - rectout.left;
				int	nHeight = rectout.bottom - rectout.top;

				POINT point[] = {
					{rectout.left + nWidth / 2 - (int) (2 * fScale), rectout.top + nHeight / 2 - (int) fScale} ,
					{rectout.left + nWidth / 2 + (int) (2 * fScale), rectout.top + nHeight / 2 - (int) fScale} ,
					{rectout.left + nWidth / 2, rectout.top + nHeight / 2 + (int) fScale}
				};

				rgn.CreatePolygonRgn(point, 3, ALTERNATE);

				CBrush Brush;
				Brush.CreateSolidBrush(RGB(0, 0 , 0));
				dc->FillRgn(&rgn, &Brush);
	#endif
			}
			else
			{
				x= ((btnWidth-5)/2) + rect->left;
				y = ((rect->bottom - rect->top -3)/2) + rect->top +1;
				dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
				dc->MoveTo(x,y);
				dc->LineTo(x+5,y);
				dc->MoveTo(x+1,y+1);
				dc->LineTo(x+4,y+1);
				dc->MoveTo(x+2,y+2);
				dc->LineTo(x+2,y+1);
			}
		}
	}

	//reset the rect
	rect->top = t;

	
	//make a line to separate the border from the rest ofthe cell
	oldpen = (CPen *)dc->SelectObject((CPen *)&pen);
	dc->MoveTo(rect->left - (int)fScale,rect->top);
	dc->LineTo(rect->left - (int)fScale,rect->bottom);
	dc->SelectObject(oldpen);
	
	//draw the text in using the default drawing routine
	rect->left = left;
	rect->right -= (int) ((btnWidth+1) * fScale);

	DrawText(dc,rect,0,col,row,cell,selected,current);

	return;
}