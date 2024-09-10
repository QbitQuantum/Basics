static int l_freeMemory (lua_State *L) {
#if defined(_WIN32) && (defined(__CYGWIN__) || defined(__CYGWIN32__))
  MEMORYSTATUS status;
  status.dwLength = sizeof(status);
  GlobalMemoryStatus( &status );
  lua_pushnumber(L, status.dwAvailPhys);
#elif defined(_WIN32)
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  GlobalMemoryStatusEx( &status );
  lua_pushnumber(L, (size_t)status.ullAvailPhys);
#else
  long pages = sysconf(_SC_AVPHYS_PAGES);
  long page_size = sysconf(_SC_PAGE_SIZE);
  lua_pushnumber(L, pages * page_size);
#endif
  return 1;
}