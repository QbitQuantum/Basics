//
// ListControlHitTest()
//
// - helper function for using the custom tooltip control with a list control
//
int CMyToolTipWnd::ListControlHitTest(CPoint point, CListCtrl& listCtl, int nColumn)
{
	// get client position
	listCtl.ScreenToClient(&point);

	// get the index of the line under the cursor
	int nIndex = -1;
	int nFirstVisible = listCtl.GetTopIndex();
	int numVisible = listCtl.GetCountPerPage();
	CRect itemRect;
	for(int i=nFirstVisible;i<nFirstVisible+numVisible;i++)
	{
		if (listCtl.GetItemRect(i, &itemRect, LVIR_BOUNDS))
		{
			if (itemRect.PtInRect(point))
			{
				nIndex = i;
				break;
			}
		}
	}

	// bail out if not on a line
	if (nIndex < 0)
		return -1;

	// else the line was found, so return if the column doesn't matter
	if (nColumn < 0)
		return nIndex;

	// else need to check if the cursor is on the right column
	BOOL bShow = FALSE;
	BOOL bInPosition = FALSE;

	// check if the cursor is within the specified col
	CRect targetRect;
//	listCtl.ClientToScreen(&itemRect);
	targetRect.left = itemRect.left;
	// NCR-FFS Changed i to j
	for(int j=0;j<nColumn;j++)
		targetRect.left += listCtl.GetColumnWidth(j);
	targetRect.right = targetRect.left + listCtl.GetColumnWidth(nColumn);
	if ((point.x >= targetRect.left) && (point.x <= targetRect.right))
	{
		// point is in the proper column, so save the rect
		CRect rect;
		listCtl.GetItemRect(nIndex, &rect, LVIR_LABEL);
		m_location.x = rect.right;
		m_location.y = rect.top;
		// account for column padding
		m_location.x += 5;
		m_location.y -= 1;
		// return the line index
		listCtl.ClientToScreen(&m_location);
		return nIndex;
	}
	else
	{
		// not within the proper column
		return -1;
	}
}