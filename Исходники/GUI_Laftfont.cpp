void GUI_Laftfont::printgl(int x, int y, int z, const wchar_t *fmt, ...)
{
	wchar_t			text[2048];
	va_list			ap;
	size_t			str_len;

	if ((!listsFont) || (!fmt)) return;

	va_start(ap, fmt);
	#ifdef WIN32
		_vsnwprintf(text, 2048, fmt, ap);
	#else
		vswprintf(text, 2048, fmt, ap);
	#endif
	va_end(ap);
	str_len = wcslen(text);

	// should be in modelview mode
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glListBase(listsFont);
	glTranslatef((float)x, (float)y, (float)z);
	glScalef(1.0f, -1.0f, 1.0f);
	#ifdef WIN32
		glCallLists((GLsizei)(str_len), GL_UNSIGNED_SHORT, text);
	#else
		glCallLists((GLsizei)(str_len), GL_UNSIGNED_INT, text);
	#endif
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	return;
}