static daoint DString_ToInteger( DString *self )
{
	if( self->mbs ) return strtoll( self->mbs, NULL, 0 );
	return wcstoll( self->wcs, NULL, 0 );
}