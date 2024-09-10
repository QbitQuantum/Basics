// usar esta de preferência a não ser que se esteja no XP ou anterior
void Consola::setTextSize(int x, int y) {
	CONSOLE_FONT_INFOEX cfont;

	cfont.cbSize=sizeof(CONSOLE_FONT_INFOEX);

	GetCurrentConsoleFontEx(hconsola, false, & cfont);
	cfont.dwFontSize.X = x;
	cfont.dwFontSize.Y = y;
	SetCurrentConsoleFontEx(hconsola, false, &cfont);
}