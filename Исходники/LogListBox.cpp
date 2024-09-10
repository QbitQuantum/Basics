LRESULT CLogListBox::OnDrawitem(UINT uMsg, WPARAM wParam, LPARAM lParam,BOOL& bHandled)
{
	LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT) lParam;
	if(!dis) return FALSE;
      
	LogListBoxItem * item = (LogListBoxItem *)dis->itemData;
	if(!item) return FALSE;
	
   CDCHandle dc = dis->hDC;

   if(dis->itemAction & (ODA_DRAWENTIRE|ODA_SELECT))
   {
		dc.SetBkColor(GetSysColor(COLOR_WINDOW));
		dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
      CRect r(dis->rcItem);
		if(!(dis->itemState & ODS_SELECTED ))
		{
			CBrush br;
			br.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
			dc.FillRect(r,br);
		}
		CRect rct;
      GetClientRect(&rct);

		if(dis->itemState & ODS_SELECTED )
		{
			CRect rd(dis->rcItem);
			GuiTools::FillRectGradient(dis->hDC,rd,0xEAE2D9, 0xD3C1AF, false);
		}
		else if(dis->itemID != GetCount()-1) // If it isn't last item
		{
			CPen pen;
			pen.CreatePen(PS_SOLID, 1, RGB(190,190,190));
			SelectObject(dc.m_hDC, pen);
			dc.MoveTo(rct.left, r.bottom-1);
			dc.LineTo(rct.right, r.bottom-1);
		}
			  
		SetBkMode(dc.m_hDC,TRANSPARENT);

		SIZE TimeLabelDimensions;
		SelectObject(dc.m_hDC, NormalFont);
		GetTextExtentPoint32(dc, item->Time, item->Time.GetLength(), &TimeLabelDimensions);
		
		// Writing error time
		
		ExtTextOutW(dc.m_hDC, rct.right-5-TimeLabelDimensions.cx, r.top + LLB_VertMargin, ETO_CLIPPED, r, item->Time, item->Time.GetLength(), 0);
		// Writing error title
		SelectObject(dc.m_hDC, UnderlineFont);
		ExtTextOutW(dc.m_hDC, r.left+56, r.top + LLB_VertMargin, ETO_CLIPPED, r, item->strTitle, wcslen(item->strTitle), 0);
		
		// Writing some info
		SelectObject(dc.m_hDC, NormalFont);
		RECT ItemRect={r.left+56, r.top + LLB_VertMargin + LLB_VertDivider + item->TitleHeight, 
							r.right - 10, r.bottom-LLB_VertMargin};
		dc.DrawText(item->Info, item->Info.GetLength() , &ItemRect, DT_NOPREFIX);
			
		// Writing error text with bold (explication of error)
		SelectObject(dc.m_hDC, BoldFont);
		RECT TextRect = {r.left+56, LLB_VertMargin +r.top+ item->TitleHeight+LLB_VertDivider+((item->Info.GetLength())?(item->InfoHeight+LLB_VertDivider):0), r.right - 10, r.bottom-LLB_VertMargin};
		dc.DrawText(item->strText,  wcslen(item->strText), &TextRect, DT_NOPREFIX);

		if(item->Type == logError)
			dc.DrawIcon(12,r.top+8,ErrorIcon);
		else if(item->Type == logWarning)
			dc.DrawIcon(12,r.top+8,WarningIcon);
	}
  
	bHandled = true;
	return 0;
}