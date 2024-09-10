static bool __is_regular_file(_STLP_fd fd) {
  struct STAT buf;
  return FSTAT(fd, &buf) == 0 && (buf.st_mode & S_IFREG) != 0 ;
}