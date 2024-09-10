void TcropNzoomPage::crop2dlg(void)
{
 setCheck(IDC_RBT_ZOOM,cfgGet(IDFF_isZoom));
 setCheck(IDC_RBT_CROP,!cfgGet(IDFF_isZoom));
 setCheck(IDC_CHB_MAGNIFICATION_LOCKED,cfgGet(IDFF_magnificationLocked));
 enableWindow(IDC_LBL_ZOOMY,!cfgGet(IDFF_magnificationLocked));
 enableWindow(IDC_TBR_ZOOMY,!cfgGet(IDFF_magnificationLocked));
 int x=cfgGet(IDFF_magnificationX);
 char s[256];
 sprintf(s,"Horizontal magnification: %i",x);
 SendDlgItemMessage(m_hwnd,IDC_LBL_ZOOMX,WM_SETTEXT,0,LPARAM(s));
 SendDlgItemMessage(m_hwnd,IDC_TBR_ZOOMX,TBM_SETPOS,TRUE,x);
 x=cfgGet(IDFF_magnificationY);
 sprintf(s,"Vertical magnification: %i",x);
 SendDlgItemMessage(m_hwnd,IDC_LBL_ZOOMY,WM_SETTEXT,0,LPARAM(s));
 SendDlgItemMessage(m_hwnd,IDC_TBR_ZOOMY,TBM_SETPOS,TRUE,x);
 SetDlgItemInt(m_hwnd,IDC_ED_CROP_LEFT  ,cfgGet(IDFF_cropLeft  ),0);
 SetDlgItemInt(m_hwnd,IDC_ED_CROP_TOP   ,cfgGet(IDFF_cropTop   ),0);
 SetDlgItemInt(m_hwnd,IDC_ED_CROP_RIGHT ,cfgGet(IDFF_cropRight ),0);
 SetDlgItemInt(m_hwnd,IDC_ED_CROP_BOTTOM,cfgGet(IDFF_cropBottom),0);
}