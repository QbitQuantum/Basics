static int io_tmpfile (lua_State *L) {
  int *pf = newfile(L);
  *pf = tmpfile();
  return (*pf == FS_OPEN_OK - 1) ? pushresult(L, 0, NULL) : 1;
}