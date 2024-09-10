static QString evilBytes( const QCString& str, bool utf8 )
{
	if ( utf8 )
	{
		return protect( str );
	}
	else
	{
		QString result;
		QCString t = protect( str ).latin1();
		int len = ( int ) t.length();
		for ( int k = 0; k < len; k++ )
		{
			if ( ( uchar ) t[k] >= 0x7f )
				result += numericEntity( ( uchar ) t[k] );
			else
				result += QChar( t[k] );
		}
		return result;
	}
}