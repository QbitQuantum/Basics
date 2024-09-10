libedit_private int
ct_chr_class(wchar_t c)
{
	if (c == '\t')
		return CHTYPE_TAB;
	else if (c == '\n')
		return CHTYPE_NL;
	else if (c < 0x100 && iswcntrl(c))
		return CHTYPE_ASCIICTL;
	else if (iswprint(c))
		return CHTYPE_PRINT;
	else
		return CHTYPE_NONPRINT;
}