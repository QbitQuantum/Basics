//---------------------------------------------------------------------------
bool HaveScrollBar(HWND hwnd)
{
  SCROLLINFO si;
  si.cbSize = sizeof(si);
  si.fMask = SIF_ALL;
  BOOL bHaveScrollBar = GetScrollInfo(hwnd, SB_VERT, &si);
  if( ! bHaveScrollBar )
    return false;
  if( si.nMax == 0 || si.nMax == 100 )
    return false;
  return true;
}