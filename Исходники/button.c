/* Set the label text (format string). */
void
AG_ButtonText(AG_Button *bu, const char *fmt, ...)
{
	char s[AG_LABEL_MAX];
	va_list ap;

	va_start(ap, fmt);
	Vsnprintf(s, sizeof(s), fmt, ap);
	va_end(ap);
	AG_ButtonTextS(bu, s);
}