void CGuiToolButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*  pdc= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	
	if( uState & ODS_SELECTED) //the button is pressed
	{
		if(m_StyleDisplay==GUISTYLE_2003 || m_StyleDisplay == GUISTYLE_2003MENUBTN)
				cb.CreateSolidBrush(GuiDrawLayer::m_Theme? RGB(249,200,102):GuiDrawLayer::GetRGBPressBXP());
			else
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBPressBXP());

	}	
	else
		if (m_bMouserOver)
		{
			if(m_StyleDisplay==GUISTYLE_2003 || m_StyleDisplay== GUISTYLE_2003MENUBTN)
				cb.CreateSolidBrush(GuiDrawLayer::m_Theme? RGB(252,230,186):GuiDrawLayer::GetRGBFondoXP());
			else
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBFondoXP());

		}
		else
		{
		
			if(m_StyleDisplay==GUISTYLE_2003)
			{
				if (m_Transparent && m_StyleDisplay )
					cb.CreateStockObject(NULL_BRUSH);
				else
				{
					CGradient M(CSize(rc.Width(),rc.Height()+1));	
					M.PrepareReverseVertTab(pdc,m_StyleDisplay);
					M.Draw(pdc,rc.left,rc.top,0,0,rc.Width(),rc.Height(),SRCCOPY);	
				}
			}
			else
				if (m_StyleDisplay== GUISTYLE_2003MENUBTN)
					cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
				else
					cb.CreateSolidBrush(m_clColor);
			
		}
	
	if (( uState & ODS_SELECTED) || m_bMouserOver )
	{
		pdc->Draw3dRect(rc,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
		rc.DeflateRect(1,1);
		
	}
	else if(m_ScrollButton || m_bSimple)
	{
		pdc->Draw3dRect(rc,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
		rc.DeflateRect(1,1);
	}

	if (m_Transparent )
		pdc->FillRect(rc,&cb);


	int calculodify;
	calculodify=rc.Height()-(m_SizeImage.cy);
	calculodify/=2;
	int nHeigh=calculodify+(m_bShowDark?1:0);
	int nWidth=m_ScrollButton?rc.Width()/2 :2;
	CPoint m_point=CPoint(nWidth,nHeigh);
	
	if (m_SizeImage.cx > 2)
	{
		if(m_bMouserOver == 1 && !(uState & ODS_DISABLED) && !(uState & ODS_SELECTED) && m_bShowDark)
		{
			CPoint p(m_point.x+1,m_point.y+1);
			pdc->DrawState(p,m_SizeImage,m_Icon,DSS_MONO,CBrush (GuiDrawLayer::GetRGBColorShadow()));
			m_point.x-=1; m_point.y-=1;
		}
		pdc->DrawState (m_point, m_SizeImage,m_Icon,
					(uState==ODS_DISABLED?DSS_DISABLED:DSS_NORMAL),(CBrush*)NULL);
	}
	if (m_SizeText.cx > 2)
	{
		int nMode = pdc->SetBkMode(TRANSPARENT);
		CRect rectletra=rc;
		int nt=m_ScrollButton?0:8;
		rectletra.left+=m_SizeImage.cx+nt;
		CPoint pt=CSize(rectletra.top,rectletra.left);
		if (uState & ODS_DISABLED)
			pdc->DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
		else
		{
			if(m_bMouserOver != 1) 
				pdc->SetTextColor(m_clrFont);
			pdc->DrawText(m_szText,rectletra,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		}
		pdc->SetBkMode(nMode);
	}
	
	// TODO:  Add your code to draw the specified item
}