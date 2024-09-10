void QUrl::decode( QString& url )
{
    if ( url.isEmpty() )
	return;

    int newlen = 0;
    QCString curl = url.utf8();
    int oldlen = curl.length();

    QCString newUrl(oldlen);

    int i = 0;
    while ( i < oldlen ) {
	uchar c = (uchar)curl[ i++ ];
	if ( c == '%' && i <= oldlen - 2 ) {
	    c = hex_to_int( (uchar)curl[ i ] ) * 16 + hex_to_int( (uchar)curl[ i + 1 ] );
	    i += 2;
	}
	newUrl [ newlen++ ] = c;
    }
    newUrl.truncate( newlen );

    url = QString::fromUtf8(newUrl.data());
}