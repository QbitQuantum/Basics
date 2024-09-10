FILE *ff_arch_misc_open_log_file_utf8(const wchar_t *filename)
{
	FILE *stream;
	
	stream = _wfsopen(filename, L"at, ccs=UTF-8", _SH_DENYWR);
	ff_winapi_fatal_error_check(stream != NULL, L"cannot open the log file [%ls], errno=%d.", filename, errno);
	return stream;
}