void MusicUtils::ConsoleWrite(CString cs)
{
	#ifdef _OPENCONSOLE
		static int si=1;
		_cwprintf_s(_T("%d-%s\n"), si,cs);
		si++;
	#endif
}