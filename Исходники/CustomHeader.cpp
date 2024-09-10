void CCustomHeader::OnPaint() 
{
	CPaintDC dc(this); 
	
	int ItemCount = GetItemCount();
	CRect cRC;
	GetClientRect(&cRC);

	CBrush brush;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_LISTHEAD);
	brush.CreatePatternBrush(&bmp);
	dc.FillRect(cRC,&brush);

	CPen pen(PS_SOLID,1,RGB(236,233,216));

	for (int i = 0 ; i <ItemCount; i++)
	{
		CRect rc;
		GetItemRect(i,rc);
		rc.DeflateRect(0,0,1,0);

		//绘制分隔条
		dc.SelectObject(&pen);
		dc.MoveTo(rc.right+1,0);
		dc.LineTo(rc.right+1,rc.Height());
		//绘制文本
		char text[100];
		memset(text,0,100);
		CListCtrl* pList =  (CListCtrl*)this->GetParent();
		if (pList != NULL)
		{
					
			LVCOLUMN col;
			memset(&col,0,sizeof(LVCOLUMN));
			col.mask = LVCF_TEXT;
			col.cchTextMax  = 100;
	
			col.pszText = (LPWSTR)text;
			pList->GetColumn(i,&col);
			dc.SetTextColor(RGB(0,0,0));

			CFont* font = GetFont();
			dc.SelectObject(font);
			dc.SetBkMode(TRANSPARENT);
			CString str ;
			str.Format(_T("%s"),text);
			dc.DrawText(str,rc,DT_CENTER |DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);
		}
	}
	pen.DeleteObject();
	bmp.DeleteObject();
	brush.DeleteObject();
}