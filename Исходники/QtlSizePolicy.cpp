int SizePolicy::transpose(lua_State * L) 
{
    QSizePolicy* lhs = QtValue<QSizePolicy>::check( L, 1 );
	lhs->transpose();
	return 0;
}