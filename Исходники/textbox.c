AG_Textbox *
AG_TextboxNew(void *parent, Uint flags, const char *fmt, ...)
{
	char s[AG_LABEL_MAX];
	va_list ap;

	if (fmt != NULL) {
		va_start(ap, fmt);
		Vsnprintf(s, sizeof(s), fmt, ap);
		va_end(ap);
		return AG_TextboxNewS(parent, flags, s);
	} else {
		return AG_TextboxNewS(parent, flags, NULL);
	}
}