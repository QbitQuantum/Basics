 BOOL CFadeStateButtonCtrlComp::CreateComponent(Component * _Parent)
 {
      SetComponentParent(_Parent);
      CFadeStateButtonCtrl::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_CtrlWindowStyle(),get_CtrlWindowStyleEx());
      HBITMAP bmp=AtlLoadBitmap(IDB_PROPERTYGRID);
      SetBitmap(bmp);
      return ::IsWindow(m_hWnd);
 }