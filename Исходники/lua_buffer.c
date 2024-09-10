/*
 * rspamd_dispatcher.create(base,fd, read_cb, write_cb, err_cb[, timeout])
 */
static int
lua_io_dispatcher_create (lua_State *L)
{
	struct rspamd_io_dispatcher_s *io_dispatcher, **pdispatcher;
	gint fd;
	struct lua_dispatcher_cbdata *cbdata;
	struct timeval tv = {0, 0};
	double tv_num, tmp;

	if (lua_gettop (L) >= 5 && lua_isfunction (L, 3) && lua_isfunction (L, 5)) {
		cbdata = g_slice_alloc0 (sizeof (struct lua_dispatcher_cbdata));
		cbdata->base = lua_check_event_base (L);
		if (cbdata->base == NULL) {
			/* Create new event base */
			msg_warn ("create new event base as it is not specified");
			cbdata->base = event_init ();
		}
		cbdata->L = L;
		fd = lua_tointeger (L, 2);
		lua_pushvalue (L, 3);
		cbdata->cbref_read = luaL_ref (L, LUA_REGISTRYINDEX);
		if (lua_isfunction (L, 4)) {
			/* Push write callback as well */
			lua_pushvalue (L, 4);
			cbdata->cbref_write = luaL_ref (L, LUA_REGISTRYINDEX);
		}
		/* Error callback */
		lua_pushvalue (L, 5);
		cbdata->cbref_err = luaL_ref (L, LUA_REGISTRYINDEX);

		if (lua_gettop (L) > 5) {
			tv_num = lua_tonumber (L, 6);
			tv.tv_sec = trunc (tv_num);
			tv.tv_usec = modf (tv_num, &tmp) * 1000.;
			io_dispatcher = rspamd_create_dispatcher (cbdata->base,
					fd,
					BUFFER_LINE,
					lua_io_read_cb,
					lua_io_write_cb,
					lua_io_err_cb,
					&tv,
					cbdata);
		}
		else {
			io_dispatcher = rspamd_create_dispatcher (cbdata->base,
					fd,
					BUFFER_LINE,
					lua_io_read_cb,
					lua_io_write_cb,
					lua_io_err_cb,
					NULL,
					cbdata);
		}

		cbdata->d = io_dispatcher;
		/* Push result */
		pdispatcher =
			lua_newuserdata (L, sizeof (struct rspamd_io_dispatcher_s *));
		rspamd_lua_setclass (L, "rspamd{io_dispatcher}", -1);
		*pdispatcher = io_dispatcher;
	}
	else {
		msg_err ("invalid number of arguments to io_dispatcher.create: %d",
			lua_gettop (L));
		lua_pushnil (L);
	}

	return 1;
}