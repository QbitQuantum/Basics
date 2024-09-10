void CMyButton::DrawButton(HDC hDestDC)
{
	CRect rc;
	GetClientRect(rc);
	int nWindth=rc.Width();
	int nHeight=rc.Height();
	HDC hDC=CreateCompatibleDC(hDestDC);//创建兼容DC,采用双缓冲画出
	HDC hMaskDC=CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);
	HBITMAP hMaskBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,hBitmap);
	HBITMAP hOldMaskBitmap=(HBITMAP)SelectObject(hMaskDC,hMaskBitmap);
	SetBkMode(hDC,TRANSPARENT);

	//把父窗口的背景图复制到按钮的DC上,实现视觉透明----------------
	CShellDlg* pParent=(CShellDlg*)GetParent();
	CPoint pt(0,0);
	MapWindowPoints(pParent,&pt,1);
	pParent->m_bkImage.BitBlt(hDC,rc,pt,SRCCOPY);


	//-------------------------------------------------------------
	int nAlpha=100;//0--255
	int nOffset=0;

	HBRUSH hbr=CreateSolidBrush(m_bkColor);
	FillRect(hMaskDC,&rc,hbr);
	DeleteObject(hbr);

	if(m_bDisable){
		nAlpha=0;//100
	}else if(m_bDown){
		nAlpha=0;//180
		nOffset=1;
	}else if(m_bOver){
		nAlpha=0;//150
	}else{
		nAlpha=0;//100
	}
	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha= nAlpha; // 透明度 最大255

	HRGN hRgn=CreateRoundRectRgn(0,0,nWindth,nHeight,3,3);
	SelectClipRgn (hDC,hRgn);
	AlphaBlend (hDC,0,0,nWindth,nHeight,hMaskDC, 0,0,nWindth,nHeight,blend);

	CString strText;
	GetWindowText(strText);
	if(strText!=_T("")){
		rc.InflateRect(-2,-2);
		rc.OffsetRect(nOffset,nOffset);
		HFONT hFont=(HFONT)SendMessage(WM_GETFONT);
		if(!hFont)hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT);
		HFONT hOldFont=(HFONT)SelectObject(hDC,hFont);
		::SetTextColor(hDC,m_textColor);
		::DrawText(hDC,strText,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_WORD_ELLIPSIS);
		::SelectObject(hDC,hOldFont);
	}
	SelectClipRgn (hDC,NULL);
	DeleteObject(hRgn);
	//复制到控件的DC上------------------------
	BitBlt(hDestDC,0,0,nWindth,nHeight,hDC,0,0,SRCCOPY);
	//删除资源,释放内存-----------------------
	SelectObject(hDC,hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hDC);
	SelectObject(hMaskDC,hOldMaskBitmap);
	DeleteObject(hMaskBitmap);
	DeleteDC(hMaskDC);

}