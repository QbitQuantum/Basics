int util_fstat(int fileno, stat_type * stat_info) {
#ifdef WINDOWS_LFS
  return _fstat64(fileno , stat_info);
#else
  return fstat(fileno , stat_info);
#endif
}