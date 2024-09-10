template<> void basic_debugbuf<wchar_t>::output_debug_string(const wchar_t *text) {
	OutputDebugStringW(text);
}