BOOL CWelcomeDlg::OnInitDialog()
{
 Super::OnInitDialog();

 //init HTTP link
 mp_secu3orgLink->SetLink(true);
 mp_secu3orgLink->SetTextColor(RGB(0, 0, 255));
 mp_secu3orgLink->SetFontUnderline(true);
 mp_secu3orgLink->SetLinkCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));

 mp_vkgLink->SetLink(true);
 mp_vkgLink->SetTextColor(RGB(0, 0, 255));
 mp_vkgLink->SetFontUnderline(true);
 mp_vkgLink->SetLinkCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));

 mp_fbgLink->SetLink(true);
 mp_fbgLink->SetTextColor(RGB(0, 0, 255));
 mp_fbgLink->SetFontUnderline(true);
 mp_fbgLink->SetLinkCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));

 m_secu3orgBmp.LoadBitmap(IDB_BITMAP0002);

 //set bitmap background
 CDC memDC;
 memDC.CreateCompatibleDC(GetDC());
 memDC.SelectObject(&m_secu3orgBmp);
 BITMAP bmp;
 m_secu3orgBmp.GetBitmap(&bmp);
 COLORREF bk_color = GetSysColor(COLOR_BTNFACE);
 for(int i = 0; i < bmp.bmWidth; ++i)
 {
  for(int j = 0; j < bmp.bmHeight; ++j)
  {
   COLORREF p = memDC.GetPixel(i,j);
   if (p > RGB(245,245,245)) //background color of original image is white
    memDC.SetPixel(i,j, bk_color);
  }
 }

 m_secu3orgPic.SetBitmap(m_secu3orgBmp);
 m_vkgBmp.LoadBitmap(IDB_BITMAP0003);
 m_vkgPic.SetBitmap(m_vkgBmp);
 m_fbgBmp.LoadBitmap(IDB_BITMAP0004);
 m_fbgPic.SetBitmap(m_fbgBmp);

 UpdateData(FALSE);
 return TRUE;  // return TRUE unless you set the focus to a control
}