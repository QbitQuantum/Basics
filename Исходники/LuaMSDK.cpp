static int lua_msdk_getDeviceId(lua_State * L)
{
	PUSHDELETESTRING(getDeviceId());
  return 1;

}