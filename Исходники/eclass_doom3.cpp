bool EntityClassDoom3_parseString( Tokeniser& tokeniser, CopiedString& s ){
	const char* token = tokeniser.getToken();
	PARSE_RETURN_FALSE_IF_FAIL( token != 0 );
	s = token;
	return true;
}