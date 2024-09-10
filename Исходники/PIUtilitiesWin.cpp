void NumToString (const long x, Str255 s)
{
	char c[33] = "";

	s [ (s[0]=0)+1 ] = 0;
	_ltoa(x, c, 10);
	AppendString(s, (const unsigned char*)&c, 0, (short)strlen(c));
}