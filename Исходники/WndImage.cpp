BOOL CWndImage::CreateFromStatic(CWnd * sc)
{
   // _ASSERTE(!::IsWindow(m_hWnd));          // image control already created
  if (!sc || !::IsWindow(sc->m_hWnd)) return false;
  CWnd * dlg = sc->GetParent();
  if (!dlg || !::IsWindow(dlg->m_hWnd)) return false;

  CRect r;
  sc->GetWindowRect(&r);
  dlg->ScreenToClient(&r);
  CString s;
  DWORD style   = sc->GetStyle();
  DWORD exstyle = sc->GetExStyle();
  sc->GetWindowText(s);
  UINT dlgID = sc->GetDlgCtrlID();

  HBITMAP bmp = (HBITMAP) sc->SendMessage(STM_GETIMAGE, IMAGE_BITMAP, 0);
  if (bmp)
     sc->SendMessage(STM_SETIMAGE, IMAGE_BITMAP, 0);

  sc->DestroyWindow();
  CreateEx(exstyle, NULL, s,  style, r, dlg, dlgID);

  if (bmp) {
    SetImg(bmp, false);
    SetBltMode(bltFitXY);
  }
  return true;
}