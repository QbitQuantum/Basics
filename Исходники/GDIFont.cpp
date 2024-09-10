// 渲染文本
void GdiFont::Printf( float x, float y, const wchar_t *format, ... )
{
	va_list l;
	va_start( l, format );

	wchar_t text[10240];
	wvsprintfW( text, format, l );

	Render( x, y, text );
}