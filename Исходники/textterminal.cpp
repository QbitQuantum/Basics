void TextTerminal::PutChar(TextBuffer* textbuf, char c)
{
	if ( ansimode )
		return PutAnsiEscaped(textbuf, c);

	if ( mbsinit(&ps) )
	{
		switch ( c )
		{
		case '\n': Newline(textbuf); return;
		case '\r': column = 0; return;
		case '\b': Backspace(textbuf); return;
		case '\t': Tab(textbuf); return;
		case '\e': AnsiReset(); return;
		case 127: return;
		default: break;
		}
	}

	wchar_t wc;
	size_t result = mbrtowc(&wc, &c, 1, &ps);
	if ( result == (size_t) -2 )
		return;
	if ( result == (size_t) -1 )
	{
		memset(&ps, 0, sizeof(ps));
		wc = L'�';
	}
	if ( result == (size_t) 0 )
		wc = L' ';

	if ( textbuf->Width() <= column )
		Newline(textbuf);
	TextPos pos(column++, line);
	TextChar tc(wc, vgacolor, ATTR_CHAR | next_attr);
	textbuf->SetChar(pos, tc);
	next_attr = 0;
}