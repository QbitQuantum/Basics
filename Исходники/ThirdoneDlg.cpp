BOOL CThirdoneDlg::OnInitDialog()
{
	ShowWindow(SW_MAXIMIZE);
	CRect rect(574,173,1130,236);
	
	
	imgfile = _T("res\\3-1.jpg");
	Show_picture(imgfile);

	CEdit *editp =(CEdit *) GetDlgItem(IDC_EDIT1);
	editp->MoveWindow( rect.left*xScale,rect.top*yScale, (rect.right-rect.left)*xScale,(rect.bottom-rect.top)*yScale );
	LOGFONT lf;     
      
	memset(&lf,0,sizeof(lf));   
	lf.lfHeight = 35;  //改变大小  
	font.CreateFontIndirect(&lf) ;	
	editp->SetFont(&font,TRUE);
	
	
	CDialogEx::OnInitDialog();
	return TRUE; 
}