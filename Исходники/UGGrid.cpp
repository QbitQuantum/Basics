/***************************************************
DrawCellsIntern
	function is the key to the fast redraw functionality in the Ultimate Grid.
	This function is responsible for drawing cells within the grid area, it
	makes sure that only the cells that are marked as invalid
	(by calling CUGDrawHint::IsInvalid function) are redrawn.
Params:
	dc		- screen DC
	db_dc	- off-screen DC, used when double buffering is enabled.
Returns:
	<none>
*****************************************************/
void CUGGrid::DrawCellsIntern(CDC *dc,CDC *db_dc)
{
	RECT		rect = {0,0,0,0};
	RECT		cellRect;
	RECT		tempRect;
	
	CUGCell		cell,tempCell;
	CString		string;
	CSize		size;

	RECT		focusRect = {-1,-1,-1,-1};
	CUGCellType * cellType;

	int			rightBlank	= -1;
	int			bottomBlank = -1;

	int			col,x;
	long		row,y;

	int			selectBlock;

	int			dcID;
	CDC*		origDC = dc;

	//double buffering
	if(m_doubleBufferMode)
	{
		origDC = dc;
		dc =  db_dc;
		//get the default font to use
		if(m_GI->m_defFont != NULL){
			origDC->SelectObject(m_GI->m_defFont);
			dc->SelectObject(m_GI->m_defFont);
		}
	}
	else{
		//get the default font to use
		if(m_GI->m_defFont != NULL){
			dc->SelectObject(m_GI->m_defFont);
		}
	}
	
	m_ctrl->OnScreenDCSetup(origDC,db_dc,UG_GRID);
	
	//set the right and bottom vars to point to
	//the extremes, if the right or bottom is
	//sooner then they will be updated in the
	//main drawing loop
	m_GI->m_rightCol = m_GI->m_numberCols;
	m_GI->m_bottomRow = m_GI->m_numberRows;
	
	//main draw loop, this loop goes through all visible
	//cells and checks to see if they need redrawing
	//if they do then the cell is retrieved and drawn
	for(y = 0; y < m_GI->m_numberRows;y++)
	{
		//skip rows hidden under locked rows
		if(y == m_GI->m_numLockRows)
			y = m_GI->m_topRow;

		row = y;

		//calc the top bottom and right side of the rect 
		//for the current cell to be drawn
		rect.top = rect.bottom;

		if(m_GI->m_uniformRowHeightFlag)
			rect.bottom += m_GI->m_defRowHeight;
		else
			rect.bottom += m_GI->m_rowHeights[row];

		if(rect.top == rect.bottom)
			continue;

		rect.right = 0;

		//check all visible cells in the current row to 
		//see if they need drawing
		for(x = 0;x < m_GI->m_numberCols;x++){

			//skip cols hidden under locked cols
			if(x == m_GI->m_numLockCols)
				x = m_GI->m_leftCol;

			row = y;
			col = x;

			//calc the left and right side of the rect
			rect.left = rect.right;
			rect.right  += m_GI->m_colInfo[col].width;

			if(rect.left == rect.right)
				continue;

			//check to see if the cell need to be redrawn
			if(m_drawHint.IsInvalid(col,row) != FALSE){
	
				//copy the rect, then use the cellRect from here
				//this is done since the cellRect may be modified
				CopyRect(&cellRect,&rect);

				//get the cell to draw
				m_ctrl->GetCellIndirect(col,row,&cell);

				//check to see if the cell is joined
				if(cell.IsPropertySet(UGCELL_JOIN_SET)){
					m_ctrl->GetCellRect(col,row,&cellRect);
					m_ctrl->GetJoinStartCell(&col,&row,&cell);
					if(m_drawHint.IsValid(col,row))
						continue;
					m_drawHint.SetAsValid(col,row);
				}

				//get the cell type to draw the cell
				if(cell.IsPropertySet(UGCELL_CELLTYPE_SET)){
					cellType = m_ctrl->GetCellType(cell.GetCellType());
				}
				else
				{
					cellType = m_ctrl->GetCellType(-1);
				}


				dcID = dc->SaveDC();

				//draw the cell, check to see if it is 'current' and/or selected
				CopyRect(&tempRect,&cellRect);
				if(row == m_GI->m_currentRow && ( col == m_GI->m_currentCol || m_GI->m_highlightRowFlag))
					cellType->OnDraw(dc,&cellRect,col,row,&cell,0,1);
				else{
					if(m_GI->m_multiSelect->IsSelected(col,row,&selectBlock))
						cellType->OnDraw(dc,&cellRect,col,row,&cell,selectBlock+1,0);
					else
						cellType->OnDraw(dc,&cellRect,col,row,&cell,0,0);
				}
				CopyRect(&cellRect,&tempRect);

				//draw a black line at the right edge of the locked columns
				if(m_GI->m_numLockCols >0){
					if(col == m_GI->m_leftCol){
						dc->SelectObject(GetStockObject(BLACK_PEN));
						dc->MoveTo(cellRect.left-1,cellRect.top);
						dc->LineTo(cellRect.left-1,cellRect.bottom+1);
					}
					else if(col == m_GI->m_numLockCols-1){
						dc->SelectObject(GetStockObject(BLACK_PEN));
						dc->MoveTo(cellRect.right-1,cellRect.top);
						dc->LineTo(cellRect.right-1,cellRect.bottom+1);
					}
				}
				//draw a black line at the bottom of the locked rows
				if(m_GI->m_numLockRows >0){
					if(row == m_GI->m_topRow ){
						dc->SelectObject(GetStockObject(BLACK_PEN));
						dc->MoveTo(cellRect.left,cellRect.top-1);
						dc->LineTo(cellRect.right+1,cellRect.top-1);
					}
					else if(row == m_GI->m_numLockRows-1){
						dc->SelectObject(GetStockObject(BLACK_PEN));
						dc->MoveTo(cellRect.left,cellRect.bottom-1);
						dc->LineTo(cellRect.right+1,cellRect.bottom-1);
					}
				}

				dc->RestoreDC(dcID);
			}

			//check to see if the focus rect should be drawn
			//this function should be called all the time
			//even if it is off screen
			if(row == m_GI->m_currentRow && (col == m_GI->m_currentCol || 
				m_GI->m_highlightRowFlag)){
				CopyRect(&focusRect,&cellRect);
			}

			//check to see if the right side of the rect is past the edge
			//of the grid drawing area, if so then break
			if(rect.right > m_GI->m_gridWidth){
				m_GI->m_rightCol = col;
				break;
			}
		
		}

		//check to see if there is blank space on the right side of the grid
		//drawing area
		if(rect.right < m_GI->m_gridWidth && m_GI->m_rightCol == m_GI->m_numberCols){
			rightBlank = rect.right;
		}

		//check to see if the bottom of the rect is past the bottom of the 
		//grid drawing area, if so then break
		if(rect.bottom > m_GI->m_gridHeight){
			m_GI->m_bottomRow = row;
			break;
		}

		//check for extra rows
		if(y >= (m_GI->m_numberRows-1)){
			long origNumRows = m_GI->m_numberRows;
			long newRow = y+1;
			m_ctrl->VerifyCurrentRow(&newRow);
			if(m_GI->m_numberRows > origNumRows){
				m_drawHint.AddHint(0,y+1,m_GI->m_numberCols-1,y+1);
			}
		}
	}

	//clear the draw hints
	m_drawHint.ClearHints();

	//check to see if there is blank space on the bottom of the grid
	//drawing area
	if(rect.bottom < m_GI->m_gridHeight && m_GI->m_bottomRow == m_GI->m_numberRows)
		bottomBlank = rect.bottom;
	
	//fill in the blank grid drawing areas
	if(rightBlank >=0 || bottomBlank >=0){
		CBrush brush(m_ctrl->OnGetDefBackColor(UG_GRID));
		GetClientRect(&rect);
		if(rightBlank >=0){
			rect.left = rightBlank;
			dc->FillRect(&rect,&brush);
		}
		if(bottomBlank >=0){
			rect.left = 0;
			rect.top = bottomBlank;
			dc->FillRect(&rect,&brush);
		}
	}

	//double buffering
	if(m_doubleBufferMode){
		dc = origDC;
		dc->BitBlt(0,0,m_GI->m_gridWidth,m_GI->m_gridHeight,db_dc,0,0,SRCCOPY);
	}	
	
	//draw the focus rect, if the flag was set above
	if(!m_tempDisableFocusRect){
		if((m_hasFocus || m_ctrl->m_findDialogRunning) && !m_ctrl->m_editInProgress)		
		{
			if(m_GI->m_highlightRowFlag)
			{
				focusRect.left = 0;

				if(rect.right < m_GI->m_gridWidth)
					focusRect.right = rect.right;
				else
				{
					if( m_GI->m_bExtend )
						focusRect.right = m_GI->m_gridWidth;
					else
					{
						int iStartCol = m_ctrl->GetLeftCol(), iEndCol = m_ctrl->GetNumberCols() - 1;
						int iWidth = 0;
						for( int iLoop = iStartCol ; iLoop <= iEndCol ; iLoop++ )
							iWidth += m_ctrl->GetColWidth( iLoop );

						focusRect.right = iWidth;
					}
				}
			}
			m_ctrl->OnDrawFocusRect(dc,&focusRect);
		}
	}

	//reset temporary flags
	m_tempDisableFocusRect = FALSE;
}