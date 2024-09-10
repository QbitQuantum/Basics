int mg_open(const char *path, int flag, int mode) { /* LCOV_EXCL_LINE */
#if defined(_WIN32) && !defined(WINCE)
  wchar_t wpath[MG_MAX_PATH];
  to_wchar(path, wpath, ARRAY_SIZE(wpath));
  return _wopen(wpath, flag, mode);
#else
  return open(path, flag, mode); /* LCOV_EXCL_LINE */
#endif
}