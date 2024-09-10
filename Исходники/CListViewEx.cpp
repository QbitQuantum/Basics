/*
	AddHeaderToolTip()
*/
BOOL CListViewEx::AddHeaderToolTip(int nCol,LPCTSTR pTooltipText/*=NULL*/)
{
	char buf[TOOLTIP_TEXT_LENGTH+1] = {0};

	// controlla il numero della colonna
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	if(nCol >= pHeader->GetItemCount())
		return(FALSE);

	// deve trovarsi in modalita' report
	if((GetStyle() & LVS_TYPEMASK)!=LVS_REPORT)
		return(FALSE);

	// get the header height
	RECT rect;
	pHeader->GetClientRect(&rect);
	RECT rctooltip;
	rctooltip.top = 0;
	rctooltip.bottom = rect.bottom;

	// now get the left and right border of the column
	rctooltip.left = 0;// - GetScrollPos(SB_HORZ);
	for(int i = 0; i < nCol; i++)
		rctooltip.left += GetListCtrl().GetColumnWidth(i);
	rctooltip.right = rctooltip.left + GetListCtrl().GetColumnWidth(nCol);

	// se non viene specificato un testo, utilizza il nome della colonna
	if(!pTooltipText)
	{
		LV_COLUMN lvcolumn = {0};
		lvcolumn.mask       = LVCF_TEXT;
		lvcolumn.pszText    = buf;
		lvcolumn.cchTextMax = TOOLTIP_TEXT_LENGTH;
		if(!GetListCtrl().GetColumn(nCol,&lvcolumn))
			return(FALSE);
	}

	// elimina e reinserisce perche' il tooltip puo' venir (re)impostato varie volte
	m_ToolTipCtrl.DelTool(GetDlgItem(0),nCol+1);
	m_ToolTipCtrl.AddTool(GetDlgItem(0),pTooltipText ? pTooltipText : buf,&rctooltip,nCol+1);
	
	return(TRUE);
}