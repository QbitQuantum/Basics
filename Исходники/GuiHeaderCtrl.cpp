//***************************************************************************
void CGuiHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		*pDC	=	CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rcitem	=	lpDrawItemStruct->rcItem;
	UINT	uState	=	lpDrawItemStruct->itemState;
	int     nItemID =   lpDrawItemStruct->itemID;
	CBrush	m_brush;
	CString m_caption;
	CSize	siImg=CSize(0,0);
	TCHAR caption[256];
	IMAGEINFO pImageInfo;
	int OldMode=pDC->SetBkMode(TRANSPARENT);
	m_brush.CreateSysColorBrush(COLOR_3DFACE);
	pDC->FillRect(rcitem,&m_brush);
	HDITEM hdi;
	hdi.mask = HDI_TEXT | HDI_FORMAT|HDI_IMAGE| HDI_ORDER;
	hdi.pszText = caption;
	hdi.cchTextMax = 255;
	GetItem( nItemID, &hdi );
	//---------------------------------------------------------
	//se mueve la imagen para dar la sensacion
	//de seleccion del item
	//---------------------------------------------------------
	if (uState == ODS_SELECTED) 
	{
		rcitem.left+=1;
		rcitem.top+=1;
	}

	if (m_nNumbottomSelect==nItemID)
	{
		DrawArrow(pDC,rcitem,m_bSentido);
		rcitem.right-=12;
	}
	
	if (hdi.iImage > -1)
	{
		m_img.GetImageInfo(hdi.iImage,&pImageInfo);
		CRect rcima =pImageInfo.rcImage;
		siImg=CSize(rcima.Width(),rcima.Height());
		CPoint pti(rcitem.left+2,rcitem.top+1);
		m_img.Draw(pDC, hdi.iImage, pti, ILD_TRANSPARENT);
	}
	if (lstrlen(caption) > 0)
		{
			CRect m_rctext=rcitem;
			m_rctext.left+=siImg.cx+4;
			m_rctext.bottom-=2;
			DrawTextExt(caption,pDC,&m_rctext,DT_SINGLELINE|DT_BOTTOM);
			
		}
	pDC->SetBkMode(OldMode);

	
}