int
main (
  int argc,
  char * * argv ) {
  wchar_t sz[100];
  char * psz = "No Name";
    setlocale(LC_ALL, "");
    if (argc >= 2) {
        psz = argv[1];
    }
    fprintf(stderr, "[%s] Standard In Begin\n", psz);
    while (fgetws(sz, sizeof (sz) / sizeof (wchar_t), stdin)) {
        fprintf(stderr, "[%s] %ls", psz, sz);
    }
    fprintf(stderr, "[%s] Standard In End\n", psz);
    fprintf(stderr, "[%s] Standard Error\n", psz);
    return (0);
}