void	IWriter::w_printf(const char* format, ...)
{
	va_list mark;
	char buf[1024];

	va_start( mark , format );
		vsprintf_s( buf , format , mark );
	va_end( mark );

	w		( buf, xr_strlen(buf) );
}