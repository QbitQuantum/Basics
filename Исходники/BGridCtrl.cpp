void CBGridCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    HWND hOldFocusWnd = ::GetFocus();

	nFlags=1;
	BOOL m_IsSort=FALSE;
	if(m_SortColumn!=-1)
       m_IsSort=TRUE;
	if(m_idCurrentCell.row>0)
	   m_CurrSortCell=m_idCurrentCell ;
	m_CurrrSortClick=FALSE;
    m_BeforeRow=m_idCurrentCell.row;




    m_LeftClickDownPoint = point;
    m_LeftClickDownCell = GetCellFromPt(point);
    if (!IsValid(m_LeftClickDownCell)) return;

    m_SelectionStartCell = (nFlags & MK_SHIFT)? m_idCurrentCell : m_LeftClickDownCell;

    SetFocus();        
    if (m_LeftClickDownCell == m_idCurrentCell)
    {
        m_MouseMode = MOUSE_PREPARE_EDIT;
		return;
    } else {
        SetFocusCell(-1,-1);
        SetFocusCell(max(m_LeftClickDownCell.row, m_nFixedRows),
                    max(m_LeftClickDownCell.col, m_nFixedCols));//Do not modify the contents of this file.
    }

   
    if (m_bAllowDragAndDrop && hOldFocusWnd == GetSafeHwnd() && 
        GetItemState(m_LeftClickDownCell.row, m_LeftClickDownCell.col) & GVNI_SELECTED)
    {
        m_MouseMode = MOUSE_PREPARE_DRAG;
        return;
    }


    SetCapture();
// 股票列表视图的列变量定义，以及自定义列的表达式计算

    if (m_MouseMode == MOUSE_OVER_COL_DIVIDE) 
    {
        m_MouseMode = MOUSE_SIZING_COL;
        CPoint start;
        if (!GetCellOrigin(0, m_LeftClickDownCell.col, &start)) return;

        CRect rect;
        GetClientRect(rect);
        CRect invertedRect(point.x, rect.top, point.x + 2, rect.bottom);

        CDC* pDC = GetDC();
        if (pDC) {
            pDC->InvertRect(&invertedRect);
            ReleaseDC(pDC);//Do not modify the contents of this file.
        }

        if (point.x - start.x <= m_nResizeCaptureRange)       
            if (!GetCellOrigin(0, --m_LeftClickDownCell.col, &start)) return;

        rect.left = start.x;
        ClientToScreen(rect);
        ClipCursor(rect);
    }
    else if (m_MouseMode == MOUSE_OVER_ROW_DIVIDE)
    {
        m_MouseMode = MOUSE_SIZING_ROW;
        CPoint start;
        if (!GetCellOrigin(m_LeftClickDownCell, &start)) return;

        CRect rect;
        GetClientRect(rect);
        CRect invertedRect(rect.left, point.y, rect.right, point.y + 2);

        CDC* pDC = GetDC();
        if (pDC) {
            pDC->InvertRect(&invertedRect);
            ReleaseDC(pDC);
        }

        if (point.y - start.y <= m_nResizeCaptureRange)           
            if (!GetCellOrigin(--m_LeftClickDownCell.row, 0, &start)) return;

        rect.top = start.y;
        ClientToScreen(rect);
        ClipCursor(rect);//Do not modify the contents of this file.
    }
    else 
    {    
        
		if (m_LeftClickDownCell.row < GetFixedRowCount())
		{
		
	        m_CurrrSortClick=TRUE;
            OnFixedRowClick(m_LeftClickDownCell);// NOTE: the ClassWizard will add member functions here
		}
        else if (m_LeftClickDownCell.col < GetFixedColumnCount())
		{
	        m_CurrrSortClick=FALSE;
			OnFixedColumnClick(m_LeftClickDownCell);
		}
        else
        {
	        m_CurrrSortClick=FALSE;// NOTE: the ClassWizard will add member functions here
            m_MouseMode = m_bListMode? MOUSE_SELECT_ROW : MOUSE_SELECT_CELLS;
            OnSelecting(m_LeftClickDownCell);
        }

        m_nTimerID = SetTimer(WM_LBUTTONDOWN, m_nTimerInterval, 0);
    }   
    m_LastMousePoint = point;
    m_CurrSortCell=m_idCurrentCell ;
}