int Polygon::remove(lua_State * L) // ( int ) 
{
	QPolygonF* obj = ValueInstaller2<QPolygonF>::check( L, 1 );
	obj->remove( Util::toInt( L, 2 ) );
	return 0;
}