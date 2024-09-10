void Derived::parse( Filereader & f, TokenStruct< std::string > & ts, Domain & d ) {
	f.next();
	f.assert( "(" );
	name = f.getToken( d.preds );
	TokenStruct< std::string > dstruct = f.parseTypedList( true, d.types );
	params = d.convertTypes( dstruct.types );

	f.next();
	f.assert( "(" );
	cond = createCondition( f, d );
	cond->parse( f, dstruct, d );

	f.next();
	f.assert( ")" );
}