int lua_PhysicsCollisionObjectCollisionListener_collisionEvent(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 3:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                (lua_type(state, 2) == LUA_TSTRING || lua_type(state, 2) == LUA_TNIL) &&
                (lua_type(state, 3) == LUA_TUSERDATA || lua_type(state, 3) == LUA_TNIL))
            {
                // Get parameter 1 off the stack.
                PhysicsCollisionObject::CollisionListener::EventType param1 = (PhysicsCollisionObject::CollisionListener::EventType)lua_enumFromString_PhysicsCollisionObjectCollisionListenerEventType(luaL_checkstring(state, 2));

                // Get parameter 2 off the stack.
                bool param2Valid;
                ScriptUtil::LuaArray<PhysicsCollisionObject::CollisionPair> param2 = ScriptUtil::getObjectPointer<PhysicsCollisionObject::CollisionPair>(3, "PhysicsCollisionObjectCollisionPair", true, &param2Valid);
                if (!param2Valid)
                {
                    lua_pushstring(state, "Failed to convert parameter 2 to type 'PhysicsCollisionObject::CollisionPair'.");
                    lua_error(state);
                }

                PhysicsCollisionObject::CollisionListener* instance = getInstance(state);
                instance->collisionEvent(param1, *param2);
                
                return 0;
            }

            lua_pushstring(state, "lua_PhysicsCollisionObjectCollisionListener_collisionEvent - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        case 4:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                (lua_type(state, 2) == LUA_TSTRING || lua_type(state, 2) == LUA_TNIL) &&
                (lua_type(state, 3) == LUA_TUSERDATA || lua_type(state, 3) == LUA_TNIL) &&
                (lua_type(state, 4) == LUA_TUSERDATA || lua_type(state, 4) == LUA_TNIL))
            {
                // Get parameter 1 off the stack.
                PhysicsCollisionObject::CollisionListener::EventType param1 = (PhysicsCollisionObject::CollisionListener::EventType)lua_enumFromString_PhysicsCollisionObjectCollisionListenerEventType(luaL_checkstring(state, 2));

                // Get parameter 2 off the stack.
                bool param2Valid;
                ScriptUtil::LuaArray<PhysicsCollisionObject::CollisionPair> param2 = ScriptUtil::getObjectPointer<PhysicsCollisionObject::CollisionPair>(3, "PhysicsCollisionObjectCollisionPair", true, &param2Valid);
                if (!param2Valid)
                {
                    lua_pushstring(state, "Failed to convert parameter 2 to type 'PhysicsCollisionObject::CollisionPair'.");
                    lua_error(state);
                }

                // Get parameter 3 off the stack.
                bool param3Valid;
                ScriptUtil::LuaArray<Vector3> param3 = ScriptUtil::getObjectPointer<Vector3>(4, "Vector3", true, &param3Valid);
                if (!param3Valid)
                {
                    lua_pushstring(state, "Failed to convert parameter 3 to type 'Vector3'.");
                    lua_error(state);
                }

                PhysicsCollisionObject::CollisionListener* instance = getInstance(state);
                instance->collisionEvent(param1, *param2, *param3);
                
                return 0;
            }

            lua_pushstring(state, "lua_PhysicsCollisionObjectCollisionListener_collisionEvent - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        case 5:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                (lua_type(state, 2) == LUA_TSTRING || lua_type(state, 2) == LUA_TNIL) &&
                (lua_type(state, 3) == LUA_TUSERDATA || lua_type(state, 3) == LUA_TNIL) &&
                (lua_type(state, 4) == LUA_TUSERDATA || lua_type(state, 4) == LUA_TNIL) &&
                (lua_type(state, 5) == LUA_TUSERDATA || lua_type(state, 5) == LUA_TNIL))
            {
                // Get parameter 1 off the stack.
                PhysicsCollisionObject::CollisionListener::EventType param1 = (PhysicsCollisionObject::CollisionListener::EventType)lua_enumFromString_PhysicsCollisionObjectCollisionListenerEventType(luaL_checkstring(state, 2));

                // Get parameter 2 off the stack.
                bool param2Valid;
                ScriptUtil::LuaArray<PhysicsCollisionObject::CollisionPair> param2 = ScriptUtil::getObjectPointer<PhysicsCollisionObject::CollisionPair>(3, "PhysicsCollisionObjectCollisionPair", true, &param2Valid);
                if (!param2Valid)
                {
                    lua_pushstring(state, "Failed to convert parameter 2 to type 'PhysicsCollisionObject::CollisionPair'.");
                    lua_error(state);
                }

                // Get parameter 3 off the stack.
                bool param3Valid;
                ScriptUtil::LuaArray<Vector3> param3 = ScriptUtil::getObjectPointer<Vector3>(4, "Vector3", true, &param3Valid);
                if (!param3Valid)
                {
                    lua_pushstring(state, "Failed to convert parameter 3 to type 'Vector3'.");
                    lua_error(state);
                }

                // Get parameter 4 off the stack.
                bool param4Valid;
                ScriptUtil::LuaArray<Vector3> param4 = ScriptUtil::getObjectPointer<Vector3>(5, "Vector3", true, &param4Valid);
                if (!param4Valid)
                {
                    lua_pushstring(state, "Failed to convert parameter 4 to type 'Vector3'.");
                    lua_error(state);
                }

                PhysicsCollisionObject::CollisionListener* instance = getInstance(state);
                instance->collisionEvent(param1, *param2, *param3, *param4);
                
                return 0;
            }

            lua_pushstring(state, "lua_PhysicsCollisionObjectCollisionListener_collisionEvent - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 3, 4 or 5).");
            lua_error(state);
            break;
        }
    }
    return 0;
}