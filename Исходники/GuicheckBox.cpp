void CGuiCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC         = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect m_rcClient(lpDrawItemStruct->rcItem);
	UINT m_State     = lpDrawItemStruct->itemState;
	CBrush cb;
	CRect m_rcTemp(m_rcClient);
	CPoint pt;
	CSize  m_Csize;
	CString m_szCaption;
	COLORREF m_Over = RGB(255, 193, 111);
	CPen cpOver(PS_SOLID, 1, RGB(255, 193, 111));
	int iMode      = pDC->SetBkMode(TRANSPARENT);
	int iExtile    = GetButtonStyle(); // obtenemos orientación del texto
	CRect m_rcText(m_rcClient);
	GetWindowText(m_szCaption);
	if (m_szCaption.GetLength() > 1)
		m_Csize= pDC->GetTextExtent(m_szCaption);

	// de acuerdo a la alineación del texto prepare la ubicación
	// del texto para Drawtex y DrawState
	
	if (m_rcClient.Height() > 13)
	{
		int Dif = m_rcClient.Height() - 13;
		Dif /= 2;
		m_rcTemp.top = Dif;
		m_rcTemp.bottom = m_rcTemp.top + 13;
	}
	if (iExtile & BS_LEFTTEXT)
	{
		m_rcTemp.left=	m_rcTemp.right - 13;
		pt = CPoint(m_rcTemp.left, m_rcTemp.top + 1);
	}
	else
	{
		m_rcTemp.right=	m_rcTemp.left + 13;
		pt = CPoint(m_rcTemp.right + 2, m_rcTemp.top + 1);
		m_rcText.left = m_rcTemp.right + 1;
	}
	
	// draw frame of checkbox
	pDC->Draw3dRect(m_rcTemp, m_clrHigh, m_clrHigh);
	m_rcTemp.DeflateRect(1, 1);
	DrawOrange(pDC, m_rcTemp);
	m_rcTemp.DeflateRect(1, 1);
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
		pDC->DrawState(pt, m_Csize, m_szCaption, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
	else 
	{
		pDC->DrawText(m_szCaption, m_rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);			   		
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			if (m_bOldTemp == TRUE)
				DrawCheck(pDC, m_rcTemp);
		}
		else
		{
			if (m_bCheckBtn == TRUE && m_bPressBtn == FALSE)
				DrawCheck(pDC, m_rcTemp);
			else
			{
				if (m_bOldTemp == TRUE && m_bPressBtn == TRUE)
					DrawCheck(pDC, m_rcTemp);
			}
		}
	}
}