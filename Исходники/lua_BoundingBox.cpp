int lua_BoundingBox_intersects(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 2:
        {
            do
            {
                if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                    (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TNIL))
                {
                    // Get parameter 1 off the stack.
                    bool param1Valid;
                    gameplay::ScriptUtil::LuaArray<BoundingBox> param1 = gameplay::ScriptUtil::getObjectPointer<BoundingBox>(2, "BoundingBox", true, &param1Valid);
                    if (!param1Valid)
                        break;

                    BoundingBox* instance = getInstance(state);
                    bool result = instance->intersects(*param1);

                    // Push the return value onto the stack.
                    lua_pushboolean(state, result);

                    return 1;
                }
            } while (0);

            do
            {
                if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                    (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TNIL))
                {
                    // Get parameter 1 off the stack.
                    bool param1Valid;
                    gameplay::ScriptUtil::LuaArray<BoundingSphere> param1 = gameplay::ScriptUtil::getObjectPointer<BoundingSphere>(2, "BoundingSphere", true, &param1Valid);
                    if (!param1Valid)
                        break;

                    BoundingBox* instance = getInstance(state);
                    bool result = instance->intersects(*param1);

                    // Push the return value onto the stack.
                    lua_pushboolean(state, result);

                    return 1;
                }
            } while (0);

            do
            {
                if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                    (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TNIL))
                {
                    // Get parameter 1 off the stack.
                    bool param1Valid;
                    gameplay::ScriptUtil::LuaArray<Frustum> param1 = gameplay::ScriptUtil::getObjectPointer<Frustum>(2, "Frustum", true, &param1Valid);
                    if (!param1Valid)
                        break;

                    BoundingBox* instance = getInstance(state);
                    bool result = instance->intersects(*param1);

                    // Push the return value onto the stack.
                    lua_pushboolean(state, result);

                    return 1;
                }
            } while (0);

            do
            {
                if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                    (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TNIL))
                {
                    // Get parameter 1 off the stack.
                    bool param1Valid;
                    gameplay::ScriptUtil::LuaArray<Plane> param1 = gameplay::ScriptUtil::getObjectPointer<Plane>(2, "Plane", true, &param1Valid);
                    if (!param1Valid)
                        break;

                    BoundingBox* instance = getInstance(state);
                    float result = instance->intersects(*param1);

                    // Push the return value onto the stack.
                    lua_pushnumber(state, result);

                    return 1;
                }
            } while (0);

            do
            {
                if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                    (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TNIL))
                {
                    // Get parameter 1 off the stack.
                    bool param1Valid;
                    gameplay::ScriptUtil::LuaArray<Ray> param1 = gameplay::ScriptUtil::getObjectPointer<Ray>(2, "Ray", true, &param1Valid);
                    if (!param1Valid)
                        break;

                    BoundingBox* instance = getInstance(state);
                    float result = instance->intersects(*param1);

                    // Push the return value onto the stack.
                    lua_pushnumber(state, result);

                    return 1;
                }
            } while (0);

            lua_pushstring(state, "lua_BoundingBox_intersects - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 2).");
            lua_error(state);
            break;
        }
    }
    return 0;
}