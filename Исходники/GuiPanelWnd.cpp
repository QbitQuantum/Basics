void CGuiPanelWnd::DrawGripper(CDC* pDC, CRect* rc)
{
	CRect gripper = rc;
	gripper.top =3;
	gripper.left+=4;
	gripper.right-=3;	
	if(m_StyleDisplay == GUISTYLE_XP)
		gripper.bottom =gripper.top +nGapGripper-3;
	if(m_StyleDisplay == GUISTYLE_2003)
		gripper.bottom =gripper.top +nGapGripper+1;
	//si la ventana esta activa pintamos el caption o el area del titulo de color azul 	
	if(!m_bActive)
	{
		if (m_StyleDisplay == GUISTYLE_2003)
		{
			CGradient M(CSize(gripper.Width(),gripper.Height()));	
			M.PrepareVertical(pDC,m_StyleDisplay);
			M.Draw(pDC,4,0,0,0,gripper.Width(),gripper.Height(),SRCCOPY);	
		}
		
		if (m_StyleDisplay == GUISTYLE_XP)
		{
			CPen cp(PS_SOLID,1,::GetSysColor(COLOR_BTNSHADOW));
			CPen* cpold=pDC->SelectObject(&cp);
			//linea superior
			pDC->MoveTo(gripper.left+1,gripper.top);
			pDC->LineTo(gripper.right,gripper.top);
			//linea izquierda
			pDC->MoveTo(gripper.left,gripper.top+1);
			pDC->LineTo(gripper.left,gripper.bottom);
			//linea inferior
			pDC->MoveTo(gripper.left+1,gripper.bottom);
			pDC->LineTo(gripper.right,gripper.bottom);
			//linea derecha
			pDC->MoveTo(gripper.right,gripper.top+1);
			pDC->LineTo(gripper.right,gripper.bottom);
			pDC->SelectObject(cpold);
		}
	}
	else
	{
		if (m_StyleDisplay == GUISTYLE_XP)
		{
			CBrush cb;
			cb.CreateSolidBrush(::GetSysColor(COLOR_ACTIVECAPTION));//GuiDrawLayer::GetRGBCaptionXP());
			pDC->FillRect(gripper,&cb);
			cb.DeleteObject();
		}
		
		if (m_StyleDisplay == GUISTYLE_2003)
		{
			CGradient M(CSize(gripper.Width(),gripper.Height()));	
			M.PrepareCaption(pDC,m_StyleDisplay);
			M.Draw(pDC,4,0,0,0,gripper.Width(),gripper.Height(),SRCCOPY);	
		}
	}

	if(m_StyleDisplay == GUISTYLE_2003) //no es XP
	{
		
		CRect rcWin=gripper;
		//rcWin.left= gripper.left;
		rcWin.top+=5;
		rcWin.left+=5;
		rcWin.right=rcWin.left+2;
		rcWin.bottom-=4;
		CRect rcBlack;

		for (int i=0; i < rcWin.Height(); i+=4)
		{
			CRect rcWindow;
			CBrush cb;
			cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
			rcWindow=rcWin;
			rcWindow.top=rcWin.top+i;
			rcWindow.bottom=rcWindow.top+2;
			pDC->FillRect(rcWindow,&cb);
			rcBlack=rcWindow;
			rcBlack.left-=1;
			rcBlack.top=(rcWin.top+i)-1;
			rcBlack.bottom=rcBlack.top+2;
			rcBlack.right=rcBlack.left+2;
			cb.DeleteObject();
			cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Theme));
			pDC->FillRect(rcBlack,&cb);
	
		}
		
			
		
	}


	gripper.DeflateRect(1, 1);
	CString m_caption;
	GetWindowText(m_caption);
	CFont m_cfont;

	m_cfont.CreateFont(-11,0,0,0,400,0,0,0,0,1,2,1,34,_T("Verdana"));
		
	CFont* m_fontOld=pDC->SelectObject(&m_cfont);
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CSize SizeCad=pDC->GetTextExtent(m_caption);
	CRect rCText=gripper;
	rCText.top=6;
	rCText.bottom =rCText.top+14;
	
	int cont=SizeCad.cx;
	while(cont > 1 && gripper.Width() > 0)
		{
			CSize coor=pDC->GetTextExtent(m_caption,m_caption.GetLength());
			if(coor.cx > gripper.Width()-10)
			{
				m_caption=m_caption.Left(m_caption.GetLength()-1);
			}
			else
				break;
			cont--;
				
		}
	if (gripper.Width() > 0	)
	if (!m_bActive)
		pDC->TextOut(rCText.left+8,rCText.top,m_caption);
	else
	{
		if (!GuiDrawLayer::m_Theme)
		pDC->SetTextColor(RGB(255,255,255));
		pDC->TextOut(rCText.left+8,rCText.top,m_caption);
	}
	//CRect gripper;
	//------------------------------------------------
	GetWindowRect( gripper );
	ScreenToClient( gripper );
	gripper.OffsetRect( -gripper.left, -gripper.top );
	gripper.left=gripper.right-20;
	gripper.right-=7;
	gripper.top+=6;
	gripper.bottom=gripper.top+13;
	m_rcCloseBtn=gripper;
	//m_rcCloseBtn.left-=4;
	//ClientToScreen(m_rcCloseBtn);
		
	m_CloseBtn.Paint(pDC,m_stateBtn,gripper,NULL_BRUSH);
		
	
	//------------------------------------------------
 	pDC->SetBkMode(nMode);
	pDC->SelectObject(m_fontOld);
	
}