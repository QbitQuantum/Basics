/** int lk::Socket::send(lua_State *L)
 * include/lk/Socket.h:181
 */
static int Socket_send(lua_State *L) {
  try {
    Socket *self = *((Socket **)dub_checksdata(L, 1, "lk.Socket"));
    lua_pushnumber(L, self->send(L));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "send: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "send: Unknown exception");
  }
  return dub_error(L);
}