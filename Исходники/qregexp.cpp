static QCString wc2rx( const QCString &pattern )
{
    int patlen = (int)pattern.length();
    QCString wcpattern("^");

    char c;
    for( int i = 0; i < patlen; i++ ) {
	c = pattern[i];
	switch ( (char)c ) {
	case '*':				// '*' ==> '.*'
	    wcpattern += '.';
	    break;
	case '?':				// '?' ==> '.'
	    c = '.';
	    break;
	case '.':				// quote special regexp chars
	case '+':
	case '\\':
	case '$':
	case '^':
	    wcpattern += '\\';
	    break;
	case '[':
	    if ( (char)pattern[i+1] == '^' ) { // don't quote '^' after '['
		wcpattern += '[';
		c = pattern[i+1];
		i++;
	    }
	    break;
	}
	wcpattern += c;

    }
    wcpattern += '$';
    return wcpattern;				// return new regexp pattern
}