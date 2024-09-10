//
// Debug string to file or message box.
//
void		CMy412MA0002TestAppDlg::UTLOut(TCHAR *strout)
{
	int			fOut, nBytes;
	if (strout == NULL) {
		DeleteFile(m_Logfile);
		return;
	}
	// U8TEXT ... Really...REALLY!
	if (!(_wsopen_s(&fOut, m_Logfile, _O_CREAT | _O_U8TEXT | _O_APPEND | _O_WRONLY, _SH_DENYNO, _S_IREAD | _S_IWRITE))) {
		nBytes = wcslen(strout) * 2;
		if ((_write(fOut, strout, nBytes)) == -1){
			;//DSWOut( L"Write failed on output\n" );
		}
		_close(fOut);
	}
	else
		;//Failed to open
}