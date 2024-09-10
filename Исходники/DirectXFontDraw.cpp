int DirectXDraw9::LoadFontFile( HMODULE module, const char *resource )
{
	void *font;
	HRSRC hres;
	unsigned long count;

	hres = FindResource( module, resource, "FONTFILE" );
	font = LockResource( LoadResource( NULL, hres ) );

	if ( AddFontMemResourceEx( font, SizeofResource( NULL, hres ), NULL, &count ) == NULL )
	{
		return 1;
	}

	return 0;
}