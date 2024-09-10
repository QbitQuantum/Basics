void CglFont::glFormat(float x, float y, float s, const int options, const char* fmt, ...)
{
	char out[512];
	va_list ap;
	if (fmt == NULL) return;
	va_start(ap, fmt);
	VSNPRINTF(out, sizeof(out), fmt, ap);
	va_end(ap);
	glPrint(x, y, s, options, std::string(out));
}