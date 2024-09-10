void CEditListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	//draw each item.set txt color,bkcolor....
	NMLVCUSTOMDRAW* pNMLVCustomDraw = (NMLVCUSTOMDRAW*)pNMHDR;
	
	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;
	
	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	
	if (pNMLVCustomDraw->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pNMLVCustomDraw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if (pNMLVCustomDraw->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
	{
		// store the colors back in the NMLVCUSTOMDRAW struct
		// but it's effective only when *pResult = CDRF_DODEFAULT 

		//	pNMLVCustomDraw->clrText = RGB(0, 0, 255);
		//	pNMLVCustomDraw->clrTextBk = RGB(0, 255, 0);
		//	*pResult = CDRF_DODEFAULT;
		
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.
		int iItem = (int)pNMLVCustomDraw->nmcd.dwItemSpec;
		int iSubItem = pNMLVCustomDraw->iSubItem;
		
		CDC* pDC = CDC::FromHandle(pNMLVCustomDraw->nmcd.hdc);
		
		CString strItemText = GetItemText(iItem, iSubItem);
		CRect rcItem, rcText;
		GetSubItemRect(iItem, iSubItem, LVIR_LABEL, rcItem);
		rcText = rcItem;
		
		CSize size = pDC->GetTextExtent(strItemText);
		if(strItemText == _T(""))
		{
			size.cx = 41; 
		}
		
		//设置文本高亮矩形
		rcText.left += 4;
		rcText.right = rcText.left + size.cx + 6;
		if(rcText.right > rcItem.right)
		{
			rcText.right = rcItem.right;
		}
		
		COLORREF crOldTextColor = pDC->GetTextColor();

		//绘制项焦点/高亮效果
		if(m_bFocus)
		{
			
			if((m_iItem == iItem) && (m_iSubItem == iSubItem))
			{	
				if(m_bHighLight)
				{					
					pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
					pDC->FillSolidRect(&rcText, ::GetSysColor(COLOR_HIGHLIGHT));
				}
				pDC->DrawFocusRect(&rcText);
			}		
		}
		
		//绘制项文本
		rcItem.left += 6;
		pDC->DrawText(strItemText, &rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOCLIP);

		pDC->SetTextColor(crOldTextColor);
		*pResult = CDRF_SKIPDEFAULT;// We've painted everything.
	}	
}