void msgff(DWORD ErrorCode, LPCWSTR Format, ...)
{
	va_list ap;
	va_start(ap, Format);
	vfwprintf(stdout, Format, ap);
	va_end(ap);
	report_error(stdout, ErrorCode);
}