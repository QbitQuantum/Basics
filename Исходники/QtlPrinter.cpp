int Printer::abort(lua_State * L) // : bool
{ 
	QPrinter* lhs = ValueBinding<MyQPrinter>::check( L, 1 );
	Util::push( L, lhs->abort() );
	return 1; 
}