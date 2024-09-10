int w_rewind(lua_State *L)
{
	if (lua_gettop(L) == 0)
	{
		instance()->rewind();
	}
	else
	{
		Source *s = luax_checksource(L, 1);
		s->rewind();
	}
	return 0;
}