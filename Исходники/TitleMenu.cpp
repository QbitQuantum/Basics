void CTitleMenu::DrawItem(LPDRAWITEMSTRUCT di)
{
	COLORREF crOldBk = ::SetBkColor(di->hDC, clLeft);

	if(m_bCanDoGradientFill&&(clLeft!=clRight))
	{
		TRIVERTEX rcVertex[2];
		di->rcItem.right--; // exclude this point, like FillRect does 
		di->rcItem.bottom--;
		rcVertex[0].x=di->rcItem.left;
		rcVertex[0].y=di->rcItem.top;
		rcVertex[0].Red=GetRValue(clLeft)<<8;	// color values from 0x0000 to 0xff00 !!!!
		rcVertex[0].Green=GetGValue(clLeft)<<8;
		rcVertex[0].Blue=GetBValue(clLeft)<<8;
		rcVertex[0].Alpha=0x0000;
		rcVertex[1].x=di->rcItem.right; 
		rcVertex[1].y=di->rcItem.bottom;
		rcVertex[1].Red=GetRValue(clRight)<<8;
		rcVertex[1].Green=GetGValue(clRight)<<8;
		rcVertex[1].Blue=GetBValue(clRight)<<8;
		rcVertex[1].Alpha=0;
		GRADIENT_RECT rect;
		rect.UpperLeft=0;
		rect.LowerRight=1;

		// fill the area
		GradientFill( di->hDC,rcVertex,2,&rect,1,GRADIENT_FILL_RECT_H);
	}
	else
	{
		::ExtTextOut(di->hDC, 0, 0, ETO_OPAQUE, &di->rcItem, NULL, 0, NULL);
	}
	if(bDrawEdge)
		::DrawEdge(di->hDC, &di->rcItem, flag_edge, BF_RECT);


	int modeOld = ::SetBkMode(di->hDC, TRANSPARENT);
	COLORREF crOld = ::SetTextColor(di->hDC, clText);
	// select font into the dc
	HFONT hfontOld = (HFONT)SelectObject(di->hDC, (HFONT)m_Font);

	// add the menu margin offset
	di->rcItem.left += GetSystemMetrics(SM_CXMENUCHECK) + 8;

	// draw the text left aligned and vertically centered
	::DrawText(di->hDC, m_strTitle, m_strTitle.GetLength(), &di->rcItem, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_NOPREFIX|DT_NOCLIP);

	//Restore font and colors...
	::SelectObject(di->hDC, hfontOld);
	::SetBkMode(di->hDC, modeOld);
	::SetBkColor(di->hDC, crOldBk);
	::SetTextColor(di->hDC, crOld);
}