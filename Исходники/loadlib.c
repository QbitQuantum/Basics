static void *ll_load (lua_State *L, const char *path) {
  HINSTANCE lib = LoadLibraryA(path);
  if (lib == NULL) pusherror(L);
  return lib;
}