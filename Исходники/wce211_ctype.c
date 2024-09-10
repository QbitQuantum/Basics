_CRTIMP wchar_t towupper(wchar_t c)
#endif
{
	return (wchar_t)toupper(c & 0xff);
}