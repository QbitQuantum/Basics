bool delete_file(const std::string &src) {
#ifdef _WIN32
  return 0 == _wunlink(Unicode(src).path());
#else
  return 0 == unlink(Unicode(src).path());
#endif
}