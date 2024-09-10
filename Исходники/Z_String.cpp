//******
//Constructor
//from c-string
//******
Z_String::Z_String( const INT8 *cStr ) {
	const int l = Strlen( cStr );
	if ( l > 0 ) {
		Concat( l, cStr );
	}
}