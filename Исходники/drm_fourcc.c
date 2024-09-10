static char printable_char(int c)
{
	return isascii(c) && isprint(c) ? c : '?';
}