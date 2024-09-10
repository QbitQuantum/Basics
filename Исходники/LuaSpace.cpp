/*
 * Function: SpawnShipNear
 *
 * Create a ship and place it in space near the given <Body>.
 *
 * > ship = Space.SpawnShip(type, body, min, max, hyperspace)
 *
 * Parameters:
 *
 *   type - the name of the ship
 *
 *   body - the <Body> near which the ship should be spawned
 *
 *   min - minimum distance from the body to place the ship, in Km
 *
 *   max - maximum distance to place the ship
 *
 *   hyperspace - optional table containing hyperspace entry information. If
 *                this is provided the ship will not spawn directly. Instead,
 *                a hyperspace cloud will be created that the ship will exit
 *                from. The table contains two elements, a <SystemPath> for
 *                the system the ship is travelling from, and the due
 *                date/time that the ship should emerge from the cloud.
 *
 * Return:
 *
 *   ship - a <Ship> object for the new ship
 *
 * Example:
 *
 * > -- spawn a ship 10km from the player
 * > local ship = Ship.SpawnNear("viper_police_craft", Game.player, 10, 10)
 *
 * Availability:
 *
 *   alpha 10
 *
 * Status:
 *
 *   experimental
 */
static int l_space_spawn_ship_near(lua_State *l)
{
    if (!Pi::game)
        luaL_error(l, "Game is not started");

    LUA_DEBUG_START(l);

    const char *type = luaL_checkstring(l, 1);
    if (! ShipType::Get(type))
        luaL_error(l, "Unknown ship type '%s'", type);

    Body *nearbody = LuaObject<Body>::CheckFromLua(2);
    float min_dist = luaL_checknumber(l, 3);
    float max_dist = luaL_checknumber(l, 4);

    SystemPath *path = 0;
    double due = -1;
    _unpack_hyperspace_args(l, 5, path, due);

    Ship *ship = new Ship(type);
    assert(ship);

    Body *thing = _maybe_wrap_ship_with_cloud(ship, path, due);

    // XXX protect against spawning inside the body
    Frame * newframe = nearbody->GetFrame();
    const vector3d newPosition = (MathUtil::RandomPointOnSphere(min_dist, max_dist)* 1000.0) + nearbody->GetPosition();

    // If the frame is rotating and the chosen position is too far, use non-rotating parent.
    // Otherwise the ship will be given a massive initial velocity when it's bumped out of the
    // rotating frame in the next update
    if (newframe->IsRotFrame() && newframe->GetRadius() < newPosition.Length()) {
        assert(newframe->GetParent());
        newframe = newframe->GetParent();
    }

    thing->SetFrame(newframe);;
    thing->SetPosition(newPosition);
    thing->SetVelocity(vector3d(0,0,0));
    Pi::game->GetSpace()->AddBody(thing);

    LuaObject<Ship>::PushToLua(ship);

    LUA_DEBUG_END(l, 1);

    return 1;
}