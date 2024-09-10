int add_keyframe(lua_State* state) {
	int args = lua_gettop(state);

	if(args != 4 && args != 5 && args != 8) {
		luaL_error(state, "Invalid number of arguments for adding keyframes");
	}

	if(!lua_isstring(state, 1)) {
		return luaL_argerror(state, 1, "animation name expected");
	}

	if(!lua_isnumber(state, 2)) {
		return luaL_argerror(state, 2, "time value expected");
	}

	if(!lua_isnumber(state, 3)) {
		return luaL_argerror(state, 3, "transition state expected");
	}

	if(!lua_isnumber(state, 4)) {
		return luaL_argerror(state, 4, "attribute expected");
	}

	if(args == 5 && !lua_isnumber(state, 5)) {
		return luaL_argerror(state, 5, "tween type expected");
	}

	if(args == 8) {
		for(int i = 5; i != 8; i++) {
			if(!lua_isnumber(state, i)) {
				return luaL_argerror(state, i, "control point coordinate expected");
			}
		}
	}

	lua_getglobal(state, "renderer");
	OpticRender* render = static_cast<OpticRender*>(lua_touserdata(state, -1));
	lua_pop(state, 1);

	try {
		if(args == 4) {
			render->addKeyframe(lua_tostring(state, 1), Keyframe(lua_tointeger(state, 2), lua_tonumber(state, 3)),
								TRANSFORM(lua_tointeger(state, 4)), LINEAR);	
		} else if(args == 5) {
			render->addKeyframe(lua_tostring(state, 1), Keyframe(lua_tointeger(state, 2), lua_tonumber(state, 3)),
								TRANSFORM(lua_tointeger(state, 4)), TWEEN(lua_tointeger(state, 5)));
		} else {
			OpticBezier bezier(lua_tonumber(state, 5), lua_tonumber(state, 6), lua_tonumber(state, 7), lua_tonumber(state, 8));
			render->addKeyframe(lua_tostring(state, 1), Keyframe(lua_tointeger(state, 2), lua_tonumber(state, 3)),
								TRANSFORM(lua_tointeger(state, 4)), bezier);
		}
	} catch(OpticException& e) {
		luaL_error(state, e.what());
	}

	return 0;
}