bool CTooltipText::RanderText(CDCHandle& dc , RECT rcRect , int iRowSpace)
{
	int iHeight = x_GetLineHeight(dc) ;
	CRect rc (rcRect.left,rcRect.top,rcRect.left,rcRect.top+iHeight) ;
	CRect rcLine (rcRect.left,rcRect.top,rcRect.left,rcRect.top+iHeight) ;
	list<CItemData>::iterator it = m_ItemList.begin() ;
	m_LinkBlockList.clear() ;

	for ( ;it!=m_ItemList.end() ; it++ )
	{
		if(TIT_RETURN == it->GetType() )
		{
			rc.bottom += iHeight ;
			rcLine.OffsetRect(CPoint(0,iHeight+iRowSpace)) ;
			rcLine.right = rcRect.left ;
		}
		else if ( TIT_LINK == it->GetType() || TIT_TEXT == it->GetType() )
		{
			CRect rcItem = it->GetRect(dc) ;
			rcLine.left = rcLine.right ;
			rcLine.right += rcItem.right ;
			rcLine.right = rcLine.right>rcRect.right ? rcRect.right : rcLine.right;
			COLORREF clrOld = dc.GetTextColor() ;
			dc.SetTextColor(it->GetColor()) ;
			if ( it->GetType() == TIT_LINK )
			{
				CFont font ;
				font.CreateFont(13,0,0,0,it->GetBold()?FW_BOLD:FW_NORMAL,0,TRUE,0,0,0,0,0,0,_T("Tahoma")) ;
				HFONT hOldFont = dc.SelectFont(font) ;

				LINKBLOCK lb = {it->GetColor(),it->GetColorHover(),it->GetColorActive(),it->GetBold(),rcLine,it->GetId(),it->GetText()};
				m_LinkBlockList.push_back(lb);

				dc.DrawText(it->GetText().c_str() , it->GetText().size() , &rcLine , DT_NOCLIP|DT_NOPREFIX |DT_SINGLELINE|DT_WORD_ELLIPSIS) ;

				dc.SelectFont(hOldFont) ;
			}
			else
				dc.DrawText(it->GetText().c_str() , it->GetText().size() , &rcLine , DT_NOCLIP|DT_NOPREFIX |DT_SINGLELINE|DT_WORD_ELLIPSIS) ;
			dc.SetTextColor(clrOld) ;
		}
	}

	return true ;

}