bool TiXmlString::operator == (const TiXmlString & compare) const
{
	if ( allocated && compare.allocated )
	{
		assert( cstring );
		assert( compare.cstring );
		return ( strcmp( cstring, compare.cstring ) == 0 );
 	}
	else if ( length() == 0 && compare.length() == 0 )
	{
		return true;
	}
	return false;
}