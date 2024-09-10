bool IsInActiveWindow(HWND hwnd)
{
  GUITHREADINFO guit; guit.cbSize = sizeof(guit);
  if(GetGUIThreadInfo(NULL, &guit))
  {
    while( ::IsWindow(hwnd) )
    {
      if( hwnd == guit.hwndActive ) return true;
      hwnd = ::GetParent(hwnd);
    }
  }
  return false;
}