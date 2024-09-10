void CRTabsCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bInit)
	{
		m_TabUpDC.CreateCompatibleDC(pdc);
		m_TabDownDC.CreateCompatibleDC(pdc);
		m_TabUp.LoadBitmap(IDB_TABUP);
		m_TabDown.LoadBitmap(IDB_TABDOWN);	
		m_TabUpDC.SelectObject(m_TabUp);
		m_TabDownDC.SelectObject(m_TabDown);
		BITMAP bitmap;
		m_TabUp.GetBitmap(&bitmap);
		m_TabUpWidth=bitmap.bmWidth;
		m_TabUpHeight=bitmap.bmHeight;
		m_TabDown.GetBitmap(&bitmap);
		m_TabDownWidth=bitmap.bmWidth;
		m_TabDownHeight=bitmap.bmHeight;
		m_bInit=FALSE;		   
	}
	int count=m_textList.GetCount();
	if (count==0) return;
//	*(char*)0=0;
	// TODO: Replace the following code with your own drawing code.
	CDC offscreenDC;
	VERIFY(offscreenDC.CreateCompatibleDC(pdc));
	CBitmap bitmap;
	CBitmap* pOldBitmap;
	VERIFY(bitmap.CreateCompatibleBitmap(pdc,rcBounds.Width(),rcBounds.Height()));
	pOldBitmap=offscreenDC.SelectObject(&bitmap);
//	offscreenDC.FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	// pre calculate the tab positions
	POSITION position = m_textList.GetHeadPosition();
	CRect rect;
	this->GetParent()->GetClientRect(rect);
	m_rectList.RemoveAll();
	m_tabList.RemoveAll();
	char* text;
    offscreenDC.SetTextAlign(TA_LEFT | TA_TOP);
    offscreenDC.SetBkMode(TRANSPARENT);
    offscreenDC.SetTextColor(TranslateColor(GetForeColor()));
    CFont* pOldFont;
	if (m_hWnd) pOldFont = offscreenDC.SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else pOldFont = offscreenDC.GetCurrentFont();
	int width;
	int start=0;
	if (m_bHorzAlign)
	{
		int finish;
		float seperation;
		int total=0;
		int laststart;
		int lastfinish;
		float lastseperation;
		BOOL lastrow=FALSE;
		BOOL notreallylastrow=FALSE;
		int row=0;
		for (int x=0;x<count;x++)
		{
			if (x==m_iCurrentSelection) lastrow=TRUE;
			text=m_textList.GetNext(position);
			width=offscreenDC.GetTextExtent(text).cx+15; // 15 is minimum seperation between text
			total+=width;
			if (total>rect.Width() || x==count-1)
			{
				// decide whether to put this tab on the next row...
				// doesnt happen if it is the only tab on the row
				if (x>start && total>rect.Width()) //|| (x-start)<3))
				{
//					finish=x-1;
//					total-=width;
					if (x==m_iCurrentSelection) notreallylastrow=TRUE;
					x--;
					if (position==NULL) position=m_textList.GetTailPosition();
					else m_textList.GetPrev(position);
					total-=width;
				}
//				else finish=x;
				finish=x;
				seperation=(float)(rect.Width()-total+(15*(finish-start+1)))/(float)(finish-start+1);
				if (lastrow==FALSE || notreallylastrow==TRUE)
					{
					DrawRow(seperation,start,finish,&offscreenDC,row,rect.Width(),FALSE);
					notreallylastrow=FALSE;
					}
				else
				{
					laststart=start;
					lastfinish=finish;
					lastseperation=seperation;
					lastrow=FALSE;
					row--;
				}
				total=0;
				start=x+1;
				row++;
			}
		}
		DrawRow(lastseperation,laststart,lastfinish,&offscreenDC,row,rect.Width(),TRUE);
	}
	else
	{
		// Draw vertical tabs.
		long widest;
		widest=CalcWidestWord();
		CRect rect2;
		this->GetClientRect(rect2);
//		widest=rect2.Width();
//		TRACE1("Measured Width: %d\n",widest);
		int y=0;
		char word[30];
		int startpos;
		BOOL NewTab;
		int oldy;
		int starty;
		for (int z=0;z<count;z++)
		{
			NewTab=TRUE;
			text=m_textList.GetNext(position);
			// split into component words
			start=0;
			startpos=2;
			starty=y;
			for (int x=0;x<(int)strlen(text)+1;x++) // includes terminating null character
			{
				if (text[x]==' ' || text[x]==NULL)
				{
					strncpy(word,text+start,min(x-start+1,30));
					word[min(x-start+1,30)]=NULL;
					start=x+1;
					width=offscreenDC.GetTextExtent(word).cx;
					if (NewTab)
					{
						if (z==m_iCurrentSelection)
						{
							DrawIconEx(offscreenDC.m_hDC,widest-400,y+2,m_hHighTabIcon,400,30,NULL,NULL,DI_NORMAL);
							offscreenDC.MoveTo(0,y);
							offscreenDC.LineTo(widest-15,y);
							offscreenDC.MoveTo(0,y+1);
							offscreenDC.LineTo(widest-10,y+1);
						}
						else DrawIconEx(offscreenDC.m_hDC,widest-402,y+2,m_hLowTabIcon,400,30,NULL,NULL,DI_NORMAL);
					}
					else
					{
						if (width+startpos>widest-15)
						{
							// Draw it at start of next line
							y+=30;
							startpos=2;
						}
						if (y!=oldy)
						{
							if (z==m_iCurrentSelection) DrawIconEx(offscreenDC.m_hDC,widest-400,y+2,m_hHighContinueIcon,400,30,NULL,NULL,DI_NORMAL);
							else DrawIconEx(offscreenDC.m_hDC,widest-402,y+2,m_hLowContinueIcon,400,30,NULL,NULL,DI_NORMAL);
						}
					}
					oldy=y; // oldy indicates that the background tab icon has been drawn for this line
					if (z==m_iCurrentSelection)
					{
						offscreenDC.ExtTextOut(startpos+2,y,ETO_CLIPPED,CRect(0,y,widest-15,y+30),word,NULL);
						if (width+startpos+2>widest-15) offscreenDC.TextOut(widest-12,y,"...");
					}
					else
					{
						offscreenDC.ExtTextOut(startpos,y+2,ETO_CLIPPED,CRect(0,y+2,widest-15,y+22),word,NULL);
						if (width+startpos>widest-15) offscreenDC.TextOut(widest-14,y+2,"...");
						offscreenDC.MoveTo(0,y+2);
						offscreenDC.LineTo(0,y+22);
						offscreenDC.MoveTo(1,y+2);
						offscreenDC.LineTo(1,y+22);
					}
					NewTab=FALSE;
					startpos+=width;
				}
			}
			y+=30;
			if (z<count-1) m_rectList.AddTail(CRect(0,starty,widest,y));
			else m_rectList.AddTail(CRect(0,starty,widest,INT_MAX));
			m_tabList.AddTail(z);
			if (z==count-1) // if at end fill remaining area with blank tab
			{
				while (y<rect2.Height())
				{
					if (z==m_iCurrentSelection) DrawIconEx(offscreenDC.m_hDC,widest-400,y+2,m_hHighContinueIcon,400,30,NULL,NULL,DI_NORMAL);
					else DrawIconEx(offscreenDC.m_hDC,widest-402,y+2,m_hLowContinueIcon,400,30,NULL,NULL,DI_NORMAL);
					y+=30;
				}
			}
		}
	}
	VERIFY(pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,&offscreenDC,
					0,0,SRCCOPY)); // flips offscreen dc to real dc
	// select out any objects that were selected in
	offscreenDC.SelectObject(pOldFont);
    offscreenDC.SelectObject(pOldBitmap);
	// then delete the dc
	offscreenDC.DeleteDC();
}