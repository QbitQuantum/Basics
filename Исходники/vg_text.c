/* Specify static text (format string). */
void
VG_TextPrintf(VG_Text *vt, const char *fmt, ...)
{
	va_list ap;

	VG_Lock(VGNODE(vt)->vg);
	if (fmt != NULL) {
		va_start(ap, fmt);
		Vsnprintf(vt->text, sizeof(vt->text), fmt, ap);
		va_end(ap);
	} else {
		vt->text[0] = '\0';
	}
	VG_Unlock(VGNODE(vt)->vg);
}