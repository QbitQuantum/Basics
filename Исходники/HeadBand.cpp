BOOL CHeadBand::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    HBITMAP hbmp = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_HEADBAND));
    CStatic* pImage = (CStatic*)GetDlgItem(IDC_IMAGE);
    pImage->SetBitmap(hbmp);
    pImage->InvalidateRect(NULL);
    pImage->UpdateWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}