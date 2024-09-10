CStringEx CTypeUnitDouble::FormatDouble( const double dvalue ) const
{
	int  decimal, sign;
	char *buffer;

	if( dvalue == 0 )
		return( CStringEx( "0.0" ));

#ifdef NL_OS_WINDOWS
	buffer = _fcvt( dvalue, 5, &decimal, &sign );
#else
	buffer = fcvt( dvalue, 5, &decimal, &sign ); 
#endif // NL_OS_WINDOWS
	CStringEx sx( buffer );
	if( decimal <= 0 )
	{
		sx = (std::string)(CStringEx( "0." ) + CStringEx( '0', -decimal ) + sx);
	}
	else
		sx.insert(decimal,".");

	while( sx[sx.length()-1] == '0' )
		sx.left( (int)sx.length() -1 );
	
	if( sx[sx.length()-1] == '.' )
		sx += '0';
	
	if( sign )
		sx = CStringEx( "-" + sx );

	return sx;
}