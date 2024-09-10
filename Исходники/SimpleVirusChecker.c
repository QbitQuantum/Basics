/* Character string comparison */
static	int	KlezTypeCheckSub( const char* name, int mask )
{
	VIRUSKEYTBL*	tbl = viruskeytbl;

	while( tbl->keyname ) {
		if( tbl->type & mask ) {
			if( !tbl->length ) {
				if( StrCmpI( name, tbl->keyname ) == 0 )
					return	1;
			} else {
				if( StrCmpNI( name, tbl->keyname, tbl->length ) == 0 )
					return	1;
			}
		}
		tbl++;
	}
	return	0;
}