bool
CExampleDlg::ToUCS2(LPTSTR pcOut, int nOutLen, const char* kpcIn)
{
	if (strlen(kpcIn) > 0) {
		// Do the conversion normally
		return MultiByteToWideChar(CP_UTF8, 0, kpcIn, -1, pcOut,
				nOutLen) > 0;
	}
	else if (nOutLen > 1) {
		// Can't distinguish no bytes copied from an error, so handle
		// an empty input string as a special case.
		_tccpy(pcOut, _T(""));
		return true;
	}
	else {
		// Not enough room to do anything!
		return false;
	}
}