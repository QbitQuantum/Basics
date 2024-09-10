void CListControlEx::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	// TODO:  添加您的代码以绘制指定项
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	LVITEM lvi = {0};
	lvi.mask = LVIF_STATE;
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ;
	lvi.iItem = lpDrawItemStruct->itemID;
	BOOL bGet = GetItem(&lvi);

	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED) && ((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS))));

	CRect rcBack = lpDrawItemStruct->rcItem;

	if( bHighlight ) //高亮显示
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
	{

		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_WINDOW)));


	}
	//绘制文本
	CString strText=L"";
	CRect rcItem;
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		for (int i = 0; i < GetHeaderCtrl()-> GetItemCount();i++)
		{            
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem ))
				continue;
			strText = GetItemText( lpDrawItemStruct->itemID, i );

			pDC->DrawText(strText,strText.GetLength(), &rcItem, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_BOTTOM);
		}
	}
}