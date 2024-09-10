void TypeGround::parse( Filereader & f, TokenStruct< std::string > & ts, Domain & d ) {
	f.next();
	params.resize( lifted->params.size() );
	for ( unsigned i = 0; i < lifted->params.size(); ++i, f.next() ) {
		std::string s = f.getToken();
		std::pair< bool, unsigned > p = d.types[lifted->params[i]]->parseObject( s );
		if ( p.first ) params[i] = p.second;
		else {
			std::pair< bool, int > q = d.types[lifted->params[i]]->parseConstant( s );
			if ( q.first ) params[i] = q.second;
			else f.tokenExit( s );
		}
	}
	f.assert_token( ")" );
}