int lua_Quaternion_conjugate(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
    case 1:
    {
        do
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Quaternion* instance = getInstance(state);
                instance->conjugate();

                return 0;
            }
        } while (0);

        lua_pushstring(state, "lua_Quaternion_conjugate - Failed to match the given parameters to a valid function signature.");
        lua_error(state);
        break;
    }
    case 2:
    {
        do
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                    (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TTABLE || lua_type(state, 2) == LUA_TNIL))
            {
                // Get parameter 1 off the stack.
                bool param1Valid;
                gameplay::ScriptUtil::LuaArray<Quaternion> param1 = gameplay::ScriptUtil::getObjectPointer<Quaternion>(2, "Quaternion", false, &param1Valid);
                if (!param1Valid)
                    break;

                Quaternion* instance = getInstance(state);
                instance->conjugate(param1);

                return 0;
            }
        } while (0);

        lua_pushstring(state, "lua_Quaternion_conjugate - Failed to match the given parameters to a valid function signature.");
        lua_error(state);
        break;
    }
    default:
    {
        lua_pushstring(state, "Invalid number of parameters (expected 1 or 2).");
        lua_error(state);
        break;
    }
    }
    return 0;
}