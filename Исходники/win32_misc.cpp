void WIN32_OP_D_FAIL(const wchar_t * _Message, const wchar_t *_File, unsigned _Line) {
	const DWORD code = GetLastError();
	pfc::array_t<wchar_t> msgFormatted; msgFormatted.set_size(pfc::strlen_t(_Message) + 64);
	wsprintfW(msgFormatted.get_ptr(), L"%s (code: %u)", _Message, code);
	if (IsDebuggerPresent()) {
		OutputDebugString(TEXT("WIN32_OP_D() failure:\n"));
		OutputDebugString(msgFormatted.get_ptr());
		OutputDebugString(TEXT("\n"));
		pfc::crash();
	}
	_wassert(msgFormatted.get_ptr(),_File,_Line);
}