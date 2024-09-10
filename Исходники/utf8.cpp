void setup_utf8() {
#ifdef UNICODE
  /*
    Ensure we write in UTF-8 mode, so that non-ASCII characters don't get
    mangled.  If we were compiled in ANSI mode it won't work.
   */
  cp = GetConsoleOutputCP();
  SetConsoleOutputCP(CP_UTF8);
  _setmode(_fileno(stdout), _O_U8TEXT);
  _setmode(_fileno(stderr), _O_U8TEXT);
#endif
}