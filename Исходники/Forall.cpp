void Forall::parse( Filereader & f, TokenStruct< std::string > & ts, Domain & d ) {
	f.next();
	f.assert( "(" );

	TokenStruct< std::string > fs = f.parseTypedList( true, d.types );
	params = d.convertTypes( fs.types );
		
	TokenStruct< std::string > fstruct( ts );
	fstruct.append( fs );

	f.next();
	f.assert( "(" );
	if ( f.getChar() != ')' ) {
		cond = createCondition( f, d );
		cond->parse( f, fstruct, d );
	}
	else ++f.c;

	f.next();
	f.assert( ")" );
}