void CGuiVisioFolder::DrawFolder(CFolderBar* cfb,Style m_Style)
{
	CRect rc=cfb->m_rect;
	CRect rcWin=cfb->m_rect;
	int nNuImage=cfb->m_img;
	CString szStringPoints=_T("...");
	CBrush cb;
	CClientDC pDC(this);
	cb.CreateSysColorBrush(COLOR_BTNFACE);
	rc.top+=1;
	pDC.FillRect(&rc,&cb);
	
	//se pintan  bordes que simulen un boton

	if (m_Style == mNormal)  //el folder no tiene el mouse 
	{
				
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorShadow());
		rc.DeflateRect(1,1);
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorShadow());
	}
	else if (m_Style == mFlat) //el mouse esta sobre el folder pero no presiona
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorShadow());
	else if (m_Style == mPush) //el mouse esta sobre el folder y presiona
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorBTNHigh());
	int OldMode=pDC.SetBkMode(TRANSPARENT);
	cfont = pDC.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CString m_cadBreak=cfb->m_lpMsg;
	int cont=m_cadBreak.GetLength();
	CSize coor=pDC.GetTextExtent(m_cadBreak,m_cadBreak.GetLength());
	CSize szImage=CSize(0,0);

	//se dibuja la imagen
	if(nNuImage != -1) 
	{
		IMAGEINFO pImageInfo;
		m_Img.GetImageInfo(nNuImage,&pImageInfo);
		CRect rcima =pImageInfo.rcImage;
		szImage=CSize(rcima.Width(),rcima.Height());
		CPoint pti=CPoint(rc.left+2,rc.top+3);
		m_Img.Draw(&pDC, nNuImage, pti, ILD_TRANSPARENT);
	}
	
	//guardar espacio para la imagen
	rc.left+=szImage.cx+4;
	rc.right-=8;
	if ( coor.cx > rc.Width())
	{
		rc.left+=1;
		while(cont > 1 )
		{
			CString m_scadtemp=m_cadBreak+szStringPoints;
			CSize coor=pDC.GetTextExtent(m_scadtemp,m_scadtemp.GetLength());
			if(coor.cx > rc.Width())
				m_cadBreak=m_cadBreak.Left(m_cadBreak.GetLength()-1);
			else
				break;
			cont--;
		}
		m_cadBreak+=szStringPoints;
		rc.right+=3;
		
			pDC.DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	}
	else
		pDC.DrawText(cfb->m_lpMsg,rc,DT_WORDBREAK|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	//----se dibuja el gripper----------

	rcWin.top+=5;
	rcWin.right-=4;
	rcWin.left=rcWin.right-3;
	rcWin.bottom-=4;

	for (int i=0; i < rcWin.Height(); i+=2)
	{
		CRect rcWindow;
		CBrush cb;
		cb.CreateSolidBrush(::GetSysColor(COLOR_BTNSHADOW));
		rcWindow=rcWin;
		rcWindow.top=rcWin.top+i;
		rcWindow.bottom=rcWindow.top+1;
		pDC.FillRect(rcWindow,&cb);
		cb.DeleteObject();			
	}
	//-------------------------
	cb.DeleteObject();
   	pDC.SetBkColor(OldMode);
	
}