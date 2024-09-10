void RemoveFile(char *fname) {
#if NACL_WINDOWS
  _unlink(fname);
#else
  unlink(fname);
#endif
}