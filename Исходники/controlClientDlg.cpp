void CcontrolClientDlg::DrawPic(CString filename)
{
	CDialog::OnPaint();
	CImage image; //使用图片类
	image.Load( filename ); //装载路径下图片信息到图片类

	RECT rect = { 0 };
	rect.bottom = image.GetWidth();
	rect.right = image.GetHeight();

	CDC* pDC = GetDlgItem(IDC_PIC)->GetWindowDC();//m_mm.GetWindowDC(); //获得显示控件的DC
	pDC->SetStretchBltMode(STRETCH_HALFTONE); 
	image.Draw( pDC->m_hDC,rect); //图片类的图片绘制Draw函数
	ReleaseDC( pDC ); 
	m_Client.LoadPic(FilePathName);
	//CopyPic();
}