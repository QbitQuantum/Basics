int mkdir(const char *path) {
  return _wmkdir(nall::utf16_t(path));
}