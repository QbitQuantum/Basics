/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	The drop list cell type draws its text using the
	base classes DrawText routine, plus draws the
	drop down button

    **See CUGCellType::OnDraw for more details
	about this function
Params
	dc		- device context to draw the cell with
	rect	- rectangle to draw the cell in
	col		- column that is being drawn
	row		- row that is being drawn
	cell	- cell that is being drawn
	selected- TRUE if the cell is selected, otherwise FALSE
	current - TRUE if the cell is the current cell, otherwise FALSE
Return
	none
****************************************************/
void CUGDropListType::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	int left = rect->left;
	RECT rectout;
	CPen * oldpen;

	int style = 0;
	if(cell->IsPropertySet(UGCELL_CELLTYPEEX_SET))
		style = cell->GetCellTypeEx();

	//if the cell is not current and hide button is on
	//then dont draw the button
	if(style&UGCT_DROPLISTHIDEBUTTON && !current){
		CUGCellType::OnDraw(dc,rect,col,row,cell,selected,current);
		return;
	}

	float fScale = 1.0;

#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	RECT rcCombo = *rect;

	rcCombo.left = rcCombo.right - (int) (fScale * m_btnWidth);


	if(!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeData, UGXPThemes::GetState(selected > 0, current > 0), &rcCombo, NULL)
		|| !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeCombo, UGXPThemes::GetState(selected > 0, current > 0), &rcCombo, NULL))
	{

		DrawBorder(dc,rect,rect,cell);

		// The printer and the monitor have different resolutions.
		// So we should adjust the size of the button.

		rect->left = rect->right - (int) (fScale * m_btnWidth);

#ifdef UG_ENABLE_PRINTING
		if (dc->IsPrinting())
		{
			rect->left += (int) fScale;
			rect->right -= (int) fScale;
			rect->top += (int) fScale;
			rect->bottom -= (int) fScale;
		}
#endif

		// draw the 3D border

		if(m_btnDown && current){
			cell->SetBorder(UG_BDR_RECESSED);
			DrawBorder(dc,rect,&rectout,cell);
		}
		else{
			cell->SetBorder(UG_BDR_RAISED);
			DrawBorder(dc,rect,&rectout,cell);
		}

		//fill the border in
		dc->FillRect(&rectout,&m_brush);
		
		//make a line to separate the border from the rest ofthe cell
		oldpen = (CPen *)dc->SelectObject((CPen *)&m_pen);
		dc->MoveTo(rect->left-1,rect->top);
		dc->LineTo(rect->left-1,rect->bottom);
		dc->SelectObject(oldpen);

		//draw the down arrow
		if (dc->IsPrinting())
		{
#ifdef UG_ENABLE_PRINTING
			CRgn rgn;

			int	nWidth = rect->right - rect->left;
			int	nHeight = rect->bottom - rect->top;

			POINT point[] = {
				{rect->left + nWidth * 3 / 10, rect->top + nHeight * 5 / 12} ,
				{rect->left + nWidth * 7 / 10, rect->top + nHeight * 5 / 12},
				{rect->left + nWidth / 2, rect->top + nHeight * 7 / 12}
			};

			rgn.CreatePolygonRgn(point, 3, ALTERNATE);

			CBrush Brush;
			Brush.CreateSolidBrush(RGB(0,0,0));
			dc->FillRgn(&rgn, &Brush);

			dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
			dc->MoveTo(rect->left,rect->top);
			dc->LineTo(rect->right,rect->top);
#endif
		}
		else
		{
			int x= (int) ((fScale * m_btnWidth-5)/2) + rect->left;
			int y = ((rect->bottom - rect->top -3)/2) + rect->top;

			// create a pen object that will be used to draw the arrow on the button
			CPen *arrowPen = NULL;
			if ( cell->GetReadOnly() == TRUE )
			{
				arrowPen = new CPen;
				arrowPen->CreatePen( PS_SOLID, 1, RGB(128,128,128));
			}
			else
				arrowPen = (CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN));

			oldpen = dc->SelectObject( arrowPen );

			// draw the arrow
			dc->MoveTo(x,y);
			dc->LineTo(x+5,y);
			dc->MoveTo(x+1,y+1);
			dc->LineTo(x+4,y+1);
			dc->MoveTo(x+2,y+2);
			dc->LineTo(x+2,y+1);

			if ( cell->GetReadOnly() == TRUE )
			{
				// clean up after temporary pen object
				dc->SelectObject(oldpen);
				arrowPen->DeleteObject();
				delete arrowPen;
				// when the arrow is disabled, add a while outline line
				dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
				dc->MoveTo(x+3,y+2);
				dc->LineTo(x+5,y);
				dc->MoveTo(x+3,y+3);
				dc->LineTo(x+6,y);
			}
		}
	}

	//draw the text in using the default drawing routine
	rect->left = left;
	rect->right -= (int) (fScale * m_btnWidth+1);

	DrawText(dc,rect,0,col,row,cell,selected,current);
}