void CButtonStyle::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	
	CDC *pDC = CDC::FromHandle(lpDIS->hDC);
	
	CString sCaption;
	CRect rect=lpDIS->rcItem;

	GetWindowText(sCaption);
	pDC->SetBkMode(TRANSPARENT);

	CFont *oldFont = pDC->SelectObject(&m_Font);
	
	m_Selected = (lpDIS->itemState & ODS_SELECTED);
	
	if((!m_bTab) || (GetDlgCtrlID()!=m_IDSelected))
	{
		if(nState==1){
			if(m_hHdc!=NULL)
				PaintBG(pDC,1);
			pDC->DrawIcon(0,3,m_hIcon1);
			pDC->SetTextColor(m_TextColorDark);
			pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}				
		else if(nState==3){
			if(m_hHdc!=NULL)
				PaintBG(pDC,3);
			if(m_Selected)
			{
				pDC->DrawIcon(1,4,m_hIcon2);
				pDC->SetTextColor(m_TextColorLight);
				pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}
			else
			{
				pDC->DrawIcon(0,3,m_hIcon2);
				pDC->SetTextColor(m_TextColorLight);
				pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}				
		}else if(nState==2){
			if(m_hHdc!=NULL)
				PaintBG(pDC,2);
			pDC->DrawIcon(0,3,m_hIcon2);
			pDC->SetTextColor(m_TextColorLight);
			pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);		
		}		
	}else
	{		
		if(m_hHdc!=NULL)
			PaintBG(pDC,1);
		pDC->DrawIcon(0,3,m_hIcon2);
		pDC->SetTextColor(m_TextColorLight);	
		pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);					
	}
	pDC->SelectObject(oldFont);					
	

}