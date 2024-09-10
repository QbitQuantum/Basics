void CColorTree::OnPaint()
{
	CTreeCtrl::OnPaint();
	CPaintDC dc(this); // device context for painting
	HTREEITEM hItem;
	CImageList *List;
			List = GetImageList(0);

	
	hItem = GetFirstVisibleItem();
	CRect rec, recText;

	 CBrush brush0(m_colRow1);
	CBrush brush1(m_colRow2);

	int i;
	i = 0;
	CDC * pDC;
	pDC = GetDC();
	CFont Font;
	Font.CreateFontW(15,0,0,0,FW_NORMAL, FALSE, FALSE,FALSE,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,FF_MODERN|DEFAULT_PITCH,_T("TestFont"));
	pDC->SelectObject(Font);
	while(hItem!=NULL)
	{
		GetItemRect(hItem,rec,FALSE);
		GetItemRect(hItem,recText,TRUE);
		//
		if(i % 2 == 0)
			{
				pDC->FillRect(rec,&brush0);
				pDC->SetBkColor(m_colRow1);
			}
		else
			{
				pDC->SetBkColor(m_colRow2);
				pDC->FillRect(rec,&brush1);
			}
		CString sName;
		sName = GetItemText(hItem);
		if(sName.Find(_T("\n"))>-1)
		{
			sName =  sName.Left(sName.Find(_T("\n")));
		}
		if(sName.Find(_T("\t"))>-1)
			{
				CString sVal;
				sVal = sName.Left(sName.Find(_T("\t")));
				pDC->TextOutW(recText.left-20 ,rec.top,sVal,sVal.GetLength());
				
				sVal = sName.Right(sName.GetLength()-1-sVal.GetLength());
				pDC->TextOutW(rec.left + (rec.right - rec.left)/2,rec.top,sVal,sVal.GetLength());
			}
		else
			pDC->TextOutW(recText.left - 20,rec.top,sName,sName.GetLength());


		if(GetItemState(hItem, TVIS_EXPANDED)& TVIS_EXPANDED)
		{
			if(List!=NULL)
			{
				CPoint xy; 		
				xy =  recText.TopLeft();
				xy.x = xy.x - 40;
				List->Draw(pDC,1,xy,ILD_NORMAL);
			}
		}
		else
		{
			if(List!=NULL)
			{
				CPoint xy; 		
				xy =  recText.TopLeft();
				xy.x = xy.x - 40;
				if(GetChildItem(hItem)!=NULL)
					List->Draw(pDC,0, xy,ILD_NORMAL);
				else
					List->Draw(pDC,2, xy,ILD_NORMAL);
			}
		}

		hItem = GetNextVisibleItem(hItem);
		i++;
	}
}