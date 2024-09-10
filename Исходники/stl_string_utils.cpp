void title_case( std::string &str )
{
	bool upper = true;
	for ( unsigned int i = 0; i<str.length(); i++ ) {
		if (upper) {
			if ( str[i] >= 'a' && str[i] <= 'z' ) {
				str[i] = _toupper( str[i] );
			}
		} else {
			if ( str[i] >= 'A' && str[i] <= 'Z' ) {
				str[i] = _tolower( str[i] );
			}
		}
		upper = isspace(str[i]);
	}
}