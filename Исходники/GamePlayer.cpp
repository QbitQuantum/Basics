void GamePlayer::ShowErrorMsg(HWND hWnd, const wchar_t* szTitle, const wchar_t* szFormat, ...)
{
	static wchar_t szError[1024];

	va_list ap;
	va_start(ap, szFormat);
	vswprintf_s(szError, szFormat, ap);
	va_end(ap);

	MessageBoxW(hWnd, szError, szTitle, MB_ICONERROR);
}