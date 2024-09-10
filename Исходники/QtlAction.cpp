int Action::setMenu(lua_State * L) // ( QMenu * menu )
{
    QAction* obj = QtObject<QAction>::check( L, 1);
    QMenu* rhs = QtObject<QMenu>::check( L, 2);
	obj->setMenu( rhs );
	return 0;
}