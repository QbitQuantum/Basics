void CComboBoxExt::DrawCombo(enTypeShow enShow,CGDI* pDC)
{

    CRect m_rcClient;
	CRect m_rcDropDown;
	GetClientRect(&m_rcClient);
	CGradient M(CSize(m_rcClient.Width(),m_rcClient.Height()));	
	M.PrepareVertical(pDC);
	M.Draw(pDC,0,0,0,0,m_rcClient.Width(),m_rcClient.Height(),SRCCOPY);
	m_rcClient.bottom-=2;
	m_rcClient.DeflateRect(1,1);

	if (enShow==CM_NORMAL)
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
	else // && !XP
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
	//debemos pintar el borde del boton drawDwon
	m_rcClient.DeflateRect(1,1);
	m_rcClient.left=m_rcClient.right-m_iWidthDrowDown;
	m_rcClient.DeflateRect(1,1);
	if (enShow!=CM_NORMAL)
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBFondoXP(),CDrawLayer::GetRGBFondoXP());
	m_rcClient.InflateRect(0,1);
	if (enShow==CM_NORMAL)
	{
		//el boton no esta seleccionado
		m_rcClient.left += 2;
		m_rcClient.right+= 2;
		DrawArrow(pDC,m_rcClient);
	}
	else

	{
		m_rcClient.InflateRect(1,1);
		CBrush cblu;
		cblu.CreateSolidBrush(enShow == CM_ONFOCUS? CDrawLayer::GetRGBFondoXP():CDrawLayer::GetRGBPressBXP());
		pDC->FillRect(&m_rcClient,&cblu);
		m_rcClient.right += 1;
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
		DrawArrow(pDC,m_rcClient);
		cblu.DeleteObject();
	}
	
}