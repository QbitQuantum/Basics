LRESULT Browse::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

	// TODO: Add your specialized code here and/or call the base class
	if (ccount==0 && message==WM_PAINT)
	{	
		Init();
	}
	if (message==WM_KEYUP || message==WM_KEYDOWN)
	{
		RECT parent,client; 
		GetWindowRect(&parent); m_ctrl.GetWindowRect(&client);
		if (m_ctrl.MousePos.x<(client.right - parent.left) && 
			m_ctrl.MousePos.x>0 &&
			m_ctrl.MousePos.y<(client.bottom - client.top) &&
			m_ctrl.MousePos.y>0)
		{
			m_ctrl.SendMessage(message,wParam,lParam);
		}
	}

	if (message==WM_MOUSEMOVE)
	{
		m_ctrl.MousePos.x = LOWORD(lParam);
		m_ctrl.MousePos.y = HIWORD(lParam);

		RECT client, parent; 
		
		ClientToScreen (&m_ctrl.MousePos);
		m_ctrl.ScreenToClient (&m_ctrl.MousePos);

		m_ctrl.GetWindowRect(&client);
		GetWindowRect(&parent);
		if (m_ctrl.MousePos.x<0)
			m_ctrl.MousePos.x=0;
		if (m_ctrl.MousePos.x>client.right-client.left)
			m_ctrl.MousePos.x=client.right-client.left;
		if (m_ctrl.MousePos.y<0)
			m_ctrl.MousePos.y=0;
		if (m_ctrl.MousePos.y>client.bottom-client.top)
			m_ctrl.MousePos.y=client.bottom-client.top;

		m_ctrl.ClientToScreen (&m_ctrl.MousePos);
		ScreenToClient (&m_ctrl.MousePos);
		
		if (lbutton) //on dessine le carre de selection
		{ 
			selection = 1;
			RECT current;
			SIZE size; size.cx = size.cy = 1;
			current.left = OriginalPos.x;
			current.top = OriginalPos.y;
			current.right = m_ctrl.MousePos.x;
			current.bottom = m_ctrl.MousePos.y;
			if (current.left>current.right) {int temp = current.left; current.left = current.right; current.right = temp;}
			if (current.top>current.bottom) {int temp = current.bottom; current.bottom = current.top; current.top = temp;}
			
			CDC *pDC = GetDC();
			m_ctrl.DrawDragRect(pDC,NULL,size,&last_sel,size);			//on efface l'ancien carre
			
			m_ctrl.UpdateSelection(&current, wParam, m_128x128);						//on affiche les modifes
			
			m_ctrl.DrawDragRect(pDC,&current,size,NULL,size);			//on affiche le nouveau carre
			::ReleaseDC(*this,*pDC);			
			
			last_sel = current;
		}
	}
	if (message==WM_DROPFILES)
	{
		m_ctrl.PostMessage(WM_DROPFILES,wParam,lParam);
	}
	if (message==WM_COMMAND && !thread_actif)
	{
		int button = LOWORD(wParam);
		if (button==IDC_ZOOM1 || button==IDC_ZOOM2 || button==IDC_ZOOM3)
		{
			m_ctrl.Zoom = button - IDC_ZOOM1 +1;
			m_ctrl.UpdateSize(m_128x128);
			m_ctrl.scrollpos = 0;
			SetScrollPos(SB_VERT,0,true);
			m_ctrl.RedrawWindow();
		}
		else if (button==IDC_INFONUM)
		{
			m_ctrl.InfoTexte = 1;
			m_ctrl.RedrawWindow();
		}			
		else if (button==IDC_FILENAME)
		{
			m_ctrl.InfoTexte =2;
			m_ctrl.RedrawWindow();
		}
		else if (button==IDC_GROUP)
		{
			m_ctrl.InfoTexte = 3;
			m_ctrl.RedrawWindow();
		}
		else if (button>=10 && button<=15) 
			m_ctrl.PostMessage(WM_COMMAND,wParam,lParam);
	}
	if (message==WM_LBUTTONDOWN)
	{
		int xPos = LOWORD(lParam);  // horizontal position of cursor 
		int yPos = HIWORD(lParam);  // vertical position of cursor 

		if (lbutton) //on dessine le carre de selection
		{ 
			selection = 1;
			RECT current;
			SIZE size; size.cx = size.cy = 1;
			current.left = OriginalPos.x;
			current.top = OriginalPos.y;
			current.right = m_ctrl.MousePos.x;
			current.bottom = m_ctrl.MousePos.y;
			if (current.left>current.right) {int temp = current.left; current.left = current.right; current.right = temp;}
			if (current.top>current.bottom) {int temp = current.bottom; current.bottom = current.top; current.top = temp;}
			
			CDC *pDC = GetDC();
			m_ctrl.DrawDragRect(pDC,NULL,size,&last_sel,size);			//on efface l'ancien carre
			
			m_ctrl.UpdateSelection(&current,wParam, m_128x128);						//on affiche les modifes
			
			::ReleaseDC(*this,*pDC);			
			
			last_sel = current;
		}
 
		RECT p,rect; p.left = m_ctrl.MousePos.x; p.top = m_ctrl.MousePos.y;
		ClientToScreen(&p); 
		m_ctrl.GetClientRect(&rect);
		POINT pt; pt.x = p.left; pt.y = p.top;
		m_ctrl.ScreenToClient(&pt);
		if (pt.x>=rect.left && pt.x<rect.right && pt.y>=rect.top && pt.y<rect.bottom) 
		{
			m_ctrl.SetFocus();
			int index = m_ctrl.GetIndex(&pt, m_128x128);
			if (index!=-1 && !(wParam&MK_SHIFT)/* && !(wParam&MK_CONTROL)*/)
			{
				tilelist::iterator p = m_ctrl.InfoList.Get(index, m_128x128);
				if (p!=m_ctrl.InfoList.GetLast(m_128x128))
				{
					tilelist::iterator pp = p;
					if (wParam&MK_CONTROL)
						p->Selected = p->Selected?0:7;
					else 
						p->Selected = 1;
					CDC *pDC = NULL;
					int indexx=0;
					for (p=m_ctrl.InfoList.GetFirst(m_128x128);p!=m_ctrl.InfoList.GetLast(m_128x128);++p, indexx++)
					{
						if (p!=pp && p->Selected)
						{
							if (!(wParam&MK_CONTROL))
							{
								p->Selected = 0;
								if (pDC==NULL) pDC = m_ctrl.GetDC();
								m_ctrl.DrawTile(p,pDC,1,m_128x128);
							}
						}
						else
						{
							if (p==pp)
							{
								if (pDC==NULL) pDC = m_ctrl.GetDC();
								m_ctrl.DrawTile(p,pDC,1,m_128x128);
							}
						}
					}
					if (pDC) ::ReleaseDC(*this,*pDC);
				}
			}
			else
			{
				if (!(wParam&MK_CONTROL) && !(wParam&MK_SHIFT))
				{
					tilelist::iterator p = m_ctrl.InfoList.GetFirst(m_128x128);
					CDC *pDC = NULL;
					for (int i = 0; i<m_ctrl.InfoList.GetSize(m_128x128); i++)
					{
						if (p->Selected)
						{
							if (pDC==NULL) pDC = m_ctrl.GetDC();
							//m_ctrl.InfoList.setSelection (i, 0);
							p->Selected = 0;
							m_ctrl.DrawTile(p,pDC,1,m_128x128);
						}
						p++;
					}
					if (pDC) ::ReleaseDC(*this,*pDC);			
				}
			}
			lbutton = 1;

			SIZE size; size.cx = size.cy = 1;

			last_sel.top = xPos;
			last_sel.left = yPos;
			last_sel.bottom = xPos;
			last_sel.right = yPos;
			OriginalPos.x=xPos;
			OriginalPos.y=yPos;
		}
	}
	if (message==WM_LBUTTONUP || message==WM_NCLBUTTONUP)
	{
		RECT p; p.left = m_ctrl.MousePos.x; p.top = m_ctrl.MousePos.y;
		ClientToScreen(&p);
		POINT pt; pt.x = p.left; pt.y = p.top;
		m_ctrl.ScreenToClient(&pt);
		int index = m_ctrl.GetIndex(&pt, m_128x128);
		if (!selection && index!=-1)
		{
			int i = 0;
		}
		else if (selection)
		{
			CDC *pDC = GetDC();
			CSize size; size.cx = size.cy = 1;
			m_ctrl.DrawDragRect(pDC,NULL,size,&last_sel,size);
			::ReleaseDC(*this,*pDC);
			int index=0;
			for (tilelist::iterator p = m_ctrl.InfoList.GetFirst(m_128x128);p!=m_ctrl.InfoList.GetLast(m_128x128);++p, index++)
			{
				if (p->Selected&3)
				{
					p->Selected=2;
				}
				else 
					p->Selected = 0;
			}
		}
		selection =0;
		lbutton = 0;
	}
	if (message==WM_KEYDOWN)
	{
		int toto = 0;
	}
	if (message==WM_SIZE && m_ctrl.count_ )
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		
		int i = max (1, m_ctrl.GetNbTileLine()); 
		int j = max (1, m_ctrl.GetNbTileColumn());
		int pos = m_ctrl.GetScrollPos(SB_VERT);
		int hview = (m_ctrl.InfoList.GetSize(m_128x128)/i + 1)*(m_ctrl.sizeicon_y + m_ctrl.spacing_y) + m_ctrl.spacing_y;
		m_ctrl.scrollpos = (pos*hview)/SCROLL_MAX;

		RECT clientrect,rect;
		m_ctrl.GetWindowRect(&clientrect);
		InvalidateRect(NULL,false);
		GetWindowRect(&rect);
		m_ctrl.SetWindowPos(NULL, 0, 0, max (100, x - 120), y - 20, SWP_NOMOVE);
		int iFirst,iLast; 
		m_ctrl.GetVisibility(iFirst, iLast, m_128x128);
		m_ctrl.UpdateBar(iFirst, iLast, m_128x128);
		return 0;
	}
	if (message==WM_VSCROLL || message==WM_MOUSEWHEEL)
	{
		SCROLLINFO inf;
		RECT rect_scroll,rect_clip;
		int scrollcode,pos;
		inf.fMask = SIF_ALL;
		GetScrollInfo(SB_VERT,&inf);
		m_ctrl.GetClientRect(&rect_scroll);
		int i = m_ctrl.GetNbTileLine();
		int hview = (m_ctrl.InfoList.GetSize(m_128x128)/i + 2)*(m_ctrl.sizeicon_y + m_ctrl.spacing_y) + m_ctrl.spacing_y;

		if (message==WM_MOUSEWHEEL)
		{
			int inc = ((int)(short)HIWORD(wParam))/WHEEL_DELTA;
			pos = inf.nPos - inc*(((m_ctrl.sizeicon_y+m_ctrl.spacing_y)*SCROLL_MAX)/(hview - m_ctrl.spacing_y));
		}
		else 
		{
			scrollcode = LOWORD(wParam);
			pos = inf.nTrackPos;
			switch (scrollcode)
			{					
				case SB_BOTTOM:
					pos = SCROLL_MAX - inf.nPage;
					break;
				case SB_PAGEDOWN:
					pos = inf.nPos + inf.nPage;
					break;
				case SB_PAGEUP:
					pos = inf.nPos - inf.nPage;
					break;
				case SB_LINEUP:
					pos = inf.nPos - (((m_ctrl.sizeicon_y+m_ctrl.spacing_y)*SCROLL_MAX)/(hview - m_ctrl.spacing_y));
					break;
				case SB_LINEDOWN:
					pos = inf.nPos + (((m_ctrl.sizeicon_y+m_ctrl.spacing_y)*SCROLL_MAX)/(hview - m_ctrl.spacing_y));
					break;
				case SB_TOP:
					pos = 0;
					break;
				case SB_THUMBPOSITION:
				case SB_ENDSCROLL:
					pos = inf.nPos;
					break;
			}
		}

		if (pos<0) pos = 0;
		if (pos>(SCROLL_MAX - (int)inf.nPage)) 
			pos = SCROLL_MAX - inf.nPage;
		
		SetScrollPos(SB_VERT,pos,1);
		rect_scroll.bottom -= rect_scroll.top;
		rect_scroll.top = 0;
		rect_clip = rect_scroll;
		int scroll_pixel = m_ctrl.scrollpos;
		int old_iFV,old_iLV;
		m_ctrl.GetVisibility(old_iFV, old_iLV, m_128x128);
		m_ctrl.scrollpos = (pos*hview)/(SCROLL_MAX);
		int iFV,iLV;
		m_ctrl.GetVisibility(iFV, iLV, m_128x128);
		
		if (iFV>old_iLV || iLV<old_iFV || scrollcode==SB_PAGEDOWN || scrollcode==SB_PAGEUP)
		{
			m_ctrl.RedrawWindow();
		}
		else
		{
			scroll_pixel -= m_ctrl.scrollpos;
			if (scroll_pixel)
			{
				CDC *pDC = m_ctrl.GetDC();
				if (abs(scroll_pixel)>(rect_clip.bottom - rect_clip.top)) scroll_pixel = 0;
				else pDC->ScrollDC(0,scroll_pixel,&rect_scroll,&rect_clip,NULL,NULL);

				tilelist::iterator p = m_ctrl.InfoList.GetFirst(m_128x128);		
				CBrush brush (GetSysColor(COLOR_3DFACE));
				if (scroll_pixel<0)
				{
					rect_scroll.top = rect_scroll.bottom + scroll_pixel;
					pDC->FillRect(&rect_scroll,&brush);
					if ((iLV-i)<iFV) i = iLV - iFV;
					int k;
					for (k = 0;k<old_iLV-i;k++) p++;
					for (k=old_iLV - i;k<=iLV;k++) 
					{
						m_ctrl.DrawTile(p,pDC,0,m_128x128);
						p++;
					}
				}
				else
				{
					rect_scroll.bottom = rect_scroll.top + scroll_pixel;
					pDC->FillRect(&rect_scroll,&brush);
					int k;
					for (k = 0;k<iFV;k++) p++;
					for (k = iFV;k<(old_iFV+i);k++)
					{
						m_ctrl.DrawTile(p,pDC,0,m_128x128);
						p++;
					}
				}
				::ReleaseDC(m_ctrl,*pDC);
			}
		}
		m_ctrl.lastVBarPos = pos;
	}
	if (message==WM_CLOSE) 
	{
		ccount=0; 
		this->m_ctrl.count_=0;
		OnDestroy();
	}
	if (message==WM_LBUTTONDBLCLK)
	{
		m_ctrl.SendMessage(WM_LBUTTONDBLCLK,wParam,lParam);
	}
	pDialog=this;
	return CDialog::WindowProc(message, wParam, lParam);
}	