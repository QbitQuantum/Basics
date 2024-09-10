BOOL WINAPI _ClipCursor(const RECT *lpRect)
{
  if ( !wmode )
  {
    if ( _ClipCursorOld )
      return _ClipCursorOld(lpRect);
    return ClipCursor(lpRect);
  }
  return TRUE;
}