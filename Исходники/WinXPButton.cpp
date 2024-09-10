 BOOL CWinXPButtonComp::CreateComponent(Component * _Parent)
 {
      SetComponentParent(_Parent);
      CWinXPButton::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_CtrlWindowStyle(),get_CtrlWindowStyleEx());
      SetBkColor(RGB(238,243,250));
      GenerateImages(_T(""), IDB_PROPERTYGRID, TRUE);
      return ::IsWindow(m_hWnd);
 }