void CLDlg::OnPaint() 
{
///////////////////////////////////////////////////////////////////////////////////////
	////OnPaint redefined 
//	CBitmap bm;
//	bm.LoadBitmap(IDB_BITMAP2);
	//DisplayBitmap(pControlDC,&bm,0,0,100,100);
	CWnd* pWnd = GetDlgItem(IDC_STATIC1);     // IDC_STATIC1 specified
                                              //  in the dialog editor
    CDC* pControlDC = pWnd->GetDC();
	
    pWnd->Invalidate();
    pWnd->UpdateWindow();

    pControlDC->SelectStockObject(0);
	pBrush=new CBrush();
	pBrush->CreateSolidBrush(RGB(50,25,50));
	CRect rect;
	rect.left=0;
	rect.top=0;
	rect.bottom=650;
	rect.right=650;
    pControlDC->Rectangle(rect);      // black square bullet
//	pControlDC->Ellipse(CRect(0,0,100,100));
	pControlDC->FillRect(rect,pBrush);

	switch(lflag)
	{
	case 0:	{
			int intrval=650/cnt;
			for(int cntr=1;cntr<cnt;cntr++)
			{
				pControlDC->MoveTo(0,intrval*cntr);
				pControlDC->LineTo(650,intrval*cntr);

			}
			}
			break;
	case 1:
		{
		if(flDV)
		{
		int interval=650/flrows[crflid];
		for(int i=1;i<flrows[crflid];i++)
		{
				pControlDC->MoveTo(0,interval*i);
				pControlDC->LineTo(650,interval*i);
			
		}
		interval=650/flclmns[crflid];
		for(i=1;i<flclmns[crflid];i++)
		{
			pControlDC->MoveTo(interval*i,0);
			pControlDC->LineTo(interval*i,650);
		}
		}
		///////// formation of labs ///////////
		CBrush *pBrush=new CBrush();
		pBrush->CreateSolidBrush(RGB(0,0,155));
		for(int tempcntr=0;tempcntr<labcount;tempcntr++)
		{
			if(labfl[tempcntr]==crflid)
			{
				//int x1=pt1[tempcntr].y*(650/flclmns[crflid]),y1=pt1[tempcntr].x*(650/flrows[crflid]) ;
				//int x2=pt2[tempcntr].y*(650/flclmns[crflid]),y2=pt2[tempcntr].x*(650/flrows[crflid]) ;
				long xx1=pt1[tempcntr].x,yy1=pt1[tempcntr].y;
				long xx2=pt2[tempcntr].x,yy2=pt2[tempcntr].y;
									

				if(xx1>xx2)
				{
					int temp=xx1;
					xx1=xx2;
					xx2=temp;
				}
				if(yy1>yy2)
				{
					int temp=yy1;
					yy1=yy2;
					yy2=temp;
				}
				char str1[30],str2[10];
				itoa(xx1,str1,10);
				itoa(yy1,str2,10);
				strcat(str1,"#");
				strcat(str1,str2);
				itoa(xx2,str2,10);
				strcat(str1,"#");
				strcat(str1,str2);
				itoa(yy2,str2,10);
				strcat(str1,"#");
				strcat(str1,str2);
				//AfxMessageBox(str1);
				pControlDC->SelectStockObject(1);
				//rect.left=5000;
				//rect.top=5000;
				//rect.right=0;
				//rect.bottom=0;
				//int xyflag=1;
				//int xleft,ytop,xright,ybottom;
				//for(int i=xx1;i<=xx2;i++)
				//	for(int j=yy1;j<=yy2;j++)
					//{
						
						rect.left=yy1*(650/flclmns[crflid]);
						rect.top=xx1*(650/flrows[crflid]);
						rect.bottom=(xx2+1)*(650/flrows[crflid]);
						rect.right=(yy2+1)*(650/flclmns[crflid]);
					
					//}
					pControlDC->FillRect(rect,pBrush);
					pControlDC->Draw3dRect(rect,COLORREF(RGB(255,0,0)),COLORREF(RGB(255,0,0)));

			
				

			}
		}
		///////// formation of labs ///////////
		
		}
		break;
	case 2:
		{
			
			int interval=650/crrows;
			for(int i=1;i<crrows;i++)
			{
					pControlDC->MoveTo(0,interval*i);
					pControlDC->LineTo(650,interval*i);
				
			}
			interval=650/crclmns;
			for(i=1;i<crclmns;i++)
			{
				pControlDC->MoveTo(interval*i,0);
				pControlDC->LineTo(interval*i,650);
			}

			//////////////////// placing computers ///////////////
			for(int tempcntr=0;tempcntr<cmcount;tempcntr++)
				{
					if(cmlabid[tempcntr]==crlabid)
					{
						long xx1=cmpt[tempcntr].x,yy1=cmpt[tempcntr].y;
						/////////////// place computer img /////////////////////
						/// ...........................
						rect.left=yy1*(650/crclmns);
						rect.top=xx1*(650/crrows);
						rect.bottom=(xx1+1)*(650/crrows);
						rect.right=(yy1+1)*(650/crclmns);
				
					//}
					pControlDC->FillRect(rect,pBrush);
					pControlDC->Draw3dRect(rect,COLORREF(RGB(255,0,0)),COLORREF(RGB(255,0,0)));

						/////////////// place computer img /////////////////////

					}
			}
			//////////////////// placing computers ///////////////

		}break;
	}
  


	pWnd->ReleaseDC(pControlDC);
////////////////////////////////////////////////////////////////////////////////////////
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
	
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}