/**
 * Adds a set of constants to the Lua library
 * @param L             A pointer to the Lua VM
 * @param LibName       The name of the library.
 * If this is an empty string, the functions will be added to the global namespace.
 * @param Constants     An array of the constant values along with their names.
 * The array must be terminated with the enry (0, 0)
 * @return              Returns true if successful, otherwise false.
 */
bool LuaBindhelper::addConstantsToLib(lua_State *L, const Common::String &libName, const lua_constant_reg *constants) {
#ifdef DEBUG
	int __startStackDepth = lua_gettop(L);
#endif

	// If the table is empty, the constants are added to the global namespace
	if (libName.size() == 0) {
		for (; constants->Name; ++constants) {
			lua_pushstring(L, constants->Name);
			lua_pushnumber(L, constants->Value);
			lua_settable(L, LUA_GLOBALSINDEX);
		}
	}
	// If the table name is nto empty, the constants are added to that table
	else {
		// Ensure that the library table exists
		if (!createTable(L, libName)) return false;

		// Register each constant in the table
		for (; constants->Name; ++constants) {
			lua_pushstring(L, constants->Name);
			lua_pushnumber(L, constants->Value);
			lua_settable(L, -3);
		}

		// Remove the library table from the Lua stack
		lua_pop(L, 1);
	}

#ifdef DEBUG
	assert(__startStackDepth == lua_gettop(L));
#endif

	return true;
}