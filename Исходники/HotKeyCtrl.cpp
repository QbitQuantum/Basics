 BOOL CHotKeyCtrl::CreateComponent(Component * _Parent)
 {
     SetComponentParent(_Parent);
     CWindowImpl<StdCtrl::CHotKeyCtrl,WTL::CHotKeyCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
     return ::IsWindow(m_hWnd);
 }