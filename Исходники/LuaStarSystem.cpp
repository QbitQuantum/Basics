/*
 * Method: GetNearbySystems
 *
 * Get a list of nearby <StarSystems> that match some criteria
 *
 * > systems = system:GetNearbySystems(range, filter)
 *
 * Parameters:
 *
 *   range - distance from this system to search, in light years
 *
 *   filter - an optional function. If specified the function will be called
 *            once for each candidate system with the <StarSystem> object
 *            passed as the only parameter. If the filter function returns
 *            true then the system will be included in the array returned by
 *            <GetNearbySystems>, otherwise it will be omitted. If no filter
 *            function is specified then all systems in range are returned.
 *
 * Return:
 *
 *  systems - an array of systems in range that matched the filter
 *
 * Availability:
 *
 *   alpha 10
 *
 * Status:
 *
 *   experimental
 */
static int l_starsystem_get_nearby_systems(lua_State *l)
{
    LUA_DEBUG_START(l);

    StarSystem *s = LuaStarSystem::CheckFromLua(1);
    double dist_ly = luaL_checknumber(l, 2);

    bool filter = false;
    if (lua_gettop(l) >= 3) {
        luaL_checktype(l, 3, LUA_TFUNCTION); // any type of function
        filter = true;
    }

    lua_newtable(l);

    SystemPath here = s->GetPath();

    int here_x = here.sectorX;
    int here_y = here.sectorY;
    int here_z = here.sectorZ;
    Uint32 here_idx = here.systemIndex;
    Sector here_sec(here_x, here_y, here_z);

    int diff_sec = int(ceil(dist_ly/Sector::SIZE));

    for (int x = here_x-diff_sec; x <= here_x+diff_sec; x++) {
        for (int y = here_y-diff_sec; y <= here_y+diff_sec; y++) {
            for (int z = here_z-diff_sec; z <= here_z+diff_sec; z++) {
                Sector sec(x, y, z);

                for (unsigned int idx = 0; idx < sec.m_systems.size(); idx++) {
                    if (x == here_x && y == here_y && z == here_z && idx == here_idx)
                        continue;

                    if (Sector::DistanceBetween(&here_sec, here_idx, &sec, idx) > dist_ly)
                        continue;

                    RefCountedPtr<StarSystem> sys = StarSystem::GetCached(SystemPath(x, y, z, idx));
                    if (filter) {
                        lua_pushvalue(l, 3);
                        LuaStarSystem::PushToLua(sys.Get());
                        lua_call(l, 1, 1);
                        if (!lua_toboolean(l, -1)) {
                            lua_pop(l, 1);
                            continue;
                        }
                        lua_pop(l, 1);
                    }

                    lua_pushinteger(l, lua_rawlen(l, -1)+1);
                    LuaStarSystem::PushToLua(sys.Get());
                    lua_rawset(l, -3);
                }
            }
        }
    }

    LUA_DEBUG_END(l, 1);

    return 1;
}