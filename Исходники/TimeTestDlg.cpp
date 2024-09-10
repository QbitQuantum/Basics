void TimeTestDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	 //绘制背景图片
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
    bmpBackground.LoadBitmap(IDB_BITMAP27); 

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0,0,rect.Width(), rect.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	

   //绘制直方图等图
	 CWnd* graphFrame = (CWnd*)GetDlgItem(IDC_STATIC);
     CDC* pDC = graphFrame->GetDC();     
	 testGraph->DrawGraph(pDC);
	 ReleaseDC(pDC);


}