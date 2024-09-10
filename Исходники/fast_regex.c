static void build_ichars( void )
{
	int c ;
	for( c=0; c<256; c++)
		ichars[c] = TOLOWER(c) ;
}