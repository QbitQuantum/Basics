HWND WinWindowCapture::FindHWND() {
  if( mHwnd && IsWindow( mHwnd ) ) {
    return mHwnd;
  }

  HWND hwnd = FindWindowW( NULL, L"Hearthstone" );

  if( !hwnd ) {
    // Fallback for localized
    HWND unityHwnd = FindWindowW( L"UnityWndClass", NULL );
    if( unityHwnd ) {
      DWORD procId;
      GetWindowThreadProcessId( unityHwnd, &procId );

      HANDLE handle = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, procId );
      TCHAR buffer[ MAX_PATH ] = { 0 };
      GetModuleFileNameEx( (HMODULE)handle, NULL, buffer, MAX_PATH );
      CloseHandle( handle );

      QString path = QString::fromWCharArray( buffer );
      if( path.contains( "Hearthstone" ) ) {
        hwnd = unityHwnd;
      }
    }
  }

  mHwnd = hwnd;
  return mHwnd;
}