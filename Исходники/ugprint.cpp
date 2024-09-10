/***************************************************
PrintPage
	Performs the actual printing of the grid cells.
	PrintInit must be called first to setup the
	printing criteria.
Params
	pDC - device context of the printer (or print preview)
	pageNum - page number to print
Return
	UG_SUCCESS - success
	UG_ERROR - failure
****************************************************/
int CUGPrint::PrintPage(CDC * pDC, int pageNum)
{
	//TEST
	if(m_bIsPreview == FALSE)
	{
		SIZE size;
		pDC->SetMapMode(MM_ANISOTROPIC);
		SetWindowExtEx(pDC->m_hDC,1,1,&size);
		SetViewportExtEx(pDC->m_hDC,m_virPixWidth,m_virPixWidth,&size);
	}

	int  x,h,w,col,xx;
	long y,row,yy;
	int startCol,endCol;
	long startRow,endRow;
	RECT cellrect={0,0,0,0};
	RECT origCellRect;
	int leftMargin = m_printLeftMarginPX;
	int topMargin =  m_printTopMarginPX;

	//get the co-ords to print
	if(GetPageFromList(pageNum,&startCol,&endCol,&startRow,&endRow) != UG_SUCCESS)
		return UG_ERROR;

	//***********************************************************
	// Caculate the column width that will be used in drawing cells.
	//***********************************************************

	CRect ColRect;
	int   nColWidth, nFirstCol; 

	m_ColRects.RemoveAll();
	ColRect.left  = leftMargin;
	ColRect.right = ColRect.left;
	nFirstCol = startCol;
	if( m_printSideHeading )
		nFirstCol = 0 - m_GI->m_numberSideHdgCols;
	for( int i = nFirstCol; i <= endCol; i++ )
	{
		if( i < 0 )
		{
			//get the side heading co-ords
			ColRect.left = ColRect.right;
			ColRect.right += (int) (m_ctrl->m_CUGSideHdg->GetSHColWidth(i) * m_printHScale);
		}
		else 
		{
			//get the left,right co-ords
			ColRect.left = ColRect.right;
			m_ctrl->GetColWidth( i, &nColWidth );
			ColRect.right += (int) (nColWidth  * m_printHScale);
		}
		m_ColRects.Add(ColRect);
	}

	//*********************
	// draw the page
	//*********************

	//draw the grid
	cellrect.top = topMargin;
	cellrect.bottom = topMargin;

	//main grid row drawing loop
	yy = startRow;
	if(m_printTopHeading)
		yy = 0 - m_GI->m_numberTopHdgRows;

	for(y = yy; y <= endRow ; y++)
	{	
		//set up the rectangle for the row
		if(y < 0 )
		{
			//set up the rect for the top heading
			cellrect.top	= cellrect.bottom;
			cellrect.bottom+= (int)(m_ctrl->m_CUGTopHdg->GetTHRowHeight(y) * m_printVScale);
			cellrect.left	= leftMargin;
			cellrect.right  = cellrect.left;
		}
		else
		{
			if(yy < 0)
			{
				yy=0;
				y = startRow;
			}
			//set up the rect for the row to be drawn
			cellrect.top	= cellrect.bottom;
			m_ctrl->GetRowHeight(y,&h);		
			cellrect.bottom += (int)(h * m_printVScale);
			cellrect.left	= leftMargin ;
			cellrect.right  = cellrect.left;
		}	

		//dont draw the row if it is 0 pixels high		
		if(cellrect.top == cellrect.bottom)
			continue;

		//main column drawing loop
		xx =startCol;
		if(m_printSideHeading)
			xx = 0 - m_GI->m_numberSideHdgCols;
		for(x = xx; x <= endCol; x++)
		{
			if( x < 0 )
			{
				//get the side heading co-ords
				cellrect.left = cellrect.right;
				cellrect.right += (int)(m_ctrl->m_CUGSideHdg->GetSHColWidth(x) * m_printHScale);
			}
			else
			{
				if(xx < 0)
				{
					xx=0;
					x = startCol;
				}
				//get the left,right co-ords
				cellrect.left = cellrect.right;
				m_ctrl->GetColWidth(x,&w);		
				cellrect.right += (int)(w * m_printHScale);
			}
		
			//dont draw the column if it is 0 pixels wide
			if(cellrect.left == cellrect.right)
				continue;

			//store the original cell rect, incase it is modified below
			CopyRect(&origCellRect,&cellrect);
	
			col = x;
			row = y;

			//check to see if the cell is a joined cell
			if(m_ctrl->GetJoinStartCell(&col,&row)==UG_SUCCESS)
			{
				RECT tempRect;
				CUGCell sourceCell, targetCell;
				int  col2, tempCol, tempCol2;
				long row2, tempRow, tempRow2;

				tempCol  = col;
				tempRow  = row;
				m_ctrl->GetJoinRange(&col,&row,&col2,&row2);
				tempCol2 = col2;
				tempRow2 = row2;

				if ((y == startRow && x == col) || (x == startCol && y == row)
					|| (y == startRow && x == startCol))
				{
					m_ctrl->GetCell (col,row,&sourceCell);
					m_ctrl->SetCell (x,y,&sourceCell);
					m_ctrl->JoinCells (x,y,col2,row2);
					col = x;
					row = y;
					m_ctrl->GetJoinRange(&col,&row,&col2,&row2);
				}
				
				if(col == x && row == y)
				{
					CopyRect(&tempRect,&cellrect);

					if (col2 > endCol || row2 > endRow)
					{
						if (col2 > endCol)
							col2 = endCol;
						if (row2 > endRow)
							row2 = endRow;
						m_ctrl->JoinCells (col,row,col2,row2);
					}
					while(col2 > col)
					{
						if (col2 <= endCol)
						{
							m_ctrl->GetColWidth(col2,&w);		
							tempRect.right+=(int)(w* m_printHScale);
						}
						col2--;
					}

					while(row2 > row)
					{
						if (row2 <= endRow)
						{
							m_ctrl->GetRowHeight(row2,&h);		
							tempRect.bottom+=(int)(h* m_printVScale);
						}
						row2--;
					}
					InternPrintCell(pDC,&tempRect,col,row);
					m_ctrl->JoinCells (tempCol,tempRow,tempCol2,tempRow2);
				}
			}
			else
			{
				InternPrintCell(pDC,&cellrect,x,y);
			}
			
			//draw a section of the print frame if selected
			CopyRect(&cellrect,&origCellRect);
		}
	}

	if ( m_printFrame )
	{	// draw left border and top border.
		if ((( m_printTopHeading ) && ( m_GI->m_numberTopHdgRows > 0 )) ||
			( startRow <= endRow))
		{
			pDC->MoveTo(leftMargin,topMargin);
			pDC->LineTo(leftMargin,cellrect.bottom-1);
			pDC->MoveTo(leftMargin,topMargin);
			pDC->LineTo(cellrect.right-1, topMargin);
		}
	}

	return UG_SUCCESS;
}