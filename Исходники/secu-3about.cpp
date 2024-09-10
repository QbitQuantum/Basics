//timeToshow - How long show splash screen, in milliseconds.
void ABOUT_API DisplaySplash(int timeToShow)
{
 USES_CONVERSION;
 CString string; CString templ = MLL::LoadString(IDS_SOFTWARE_INFO);
 string.Format(templ, A2T(__DATE__)); //compiler uses only ASCII format...

 AboutStc(CWnd::GetDesktopWindow(), hInstance, (LPCTSTR)IDB_BITMAP0001, (LPCTSTR)IDR_RGN0001,
	 string, MLL::LoadString(IDS_AUTHOR_INFO), true, timeToShow);
}