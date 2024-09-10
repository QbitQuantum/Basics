int
vswprintf(wchar_t* s, size_t n, const wchar_t* fmt, va_list args)
{
	Sfio_t	f;
	int	v;

	if (!s)
		return -1;

	/*
	 * make a fake stream
	 */

	SFCLEAR(&f, NiL);
	f.flags = SF_STRING|SF_WRITE;
	f.bits = SF_PRIVATE;
	f.mode = SF_WRITE;
	f.size = n - 1;
	f.data = f.next = f.endr = (uchar*)s;
	f.endb = f.endw = f.data + f.size;

	/*
	 * call and adjust
	 */

	v = vfwprintf(&f, fmt, args);
	*f.next = 0;
	_Sfi = f.next - f.data;
	return v;
}