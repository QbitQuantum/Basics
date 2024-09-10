bool _cdecl CScript::WriteSection( LPCTSTR pszSection, ... )
{
	ADDTOCALLSTACK_INTENSIVE("CScript::WriteSection");
	// Write out the section header.
	va_list vargs;
	va_start( vargs, pszSection );

	// EndSection();	// End any previous section.
	Printf( "\n[");
	VPrintf( pszSection, vargs );
	Printf( "]\n" );
	va_end( vargs );

	return( true );
}