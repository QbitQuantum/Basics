static int jiveL_dns_gc(lua_State *L) {
	struct dns_userdata *u;

	u = lua_touserdata(L, 1);
	CLOSESOCKET(u->fd[0]);
	CLOSESOCKET(u->fd[1]);

	return 0;
}