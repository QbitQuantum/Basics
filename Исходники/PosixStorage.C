inline int openFile(const FChar *s) {
#ifdef SP_WIDE_SYSTEM
    return _wopen(s, O_RDONLY|O_BINARY);
#else
    return ::open(s, O_RDONLY|O_BINARY);
#endif
  }