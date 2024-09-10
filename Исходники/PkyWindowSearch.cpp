HWND PkyWindowSearch::FindMessageWindow( HWND wnd, const wchar_t* pszWndClass, const wchar_t* pszWndText )
{
  return FindWindowExW( HWND_MESSAGE, wnd, pszWndClass, pszWndText );
}