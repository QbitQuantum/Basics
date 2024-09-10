unsigned int _mbbtoupper(unsigned int c)
{
	if (!_ismbblead(c) )
		return toupper(c);

	return c;
}