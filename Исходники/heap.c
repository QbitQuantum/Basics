void heap_cmd(int argc, char **argv) {
  char libname[72];
  int len;

  heap_options_parse(argc, argv);

  len = strlen(heap_options_tmppath);

  if(len > 64 || len <= 0)
    R_UTILS_ERRX("Bad tmp path len ! (can't excess 64 chars)");

  strcpy(libname, heap_options_tmppath);

  if(libname[len-1] != '/') {
    libname[len] = '/';
    libname[len+1] = 0;
    len++;
  }

  strcat(libname, "libheap_tmp.so");
  heap_dump_lib(libname);

  if(setenv("LD_PRELOAD", libname, 1) == -1) {
    fprintf(stderr, "Can't set LD_PRELOAD environment variable\n");
    exit(EXIT_FAILURE);
  }

  if(heap_options_color)
    if(setenv("LIBHEAP_COLOR", "1", 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_COLOR environment variable\n");
      exit(EXIT_FAILURE);
    }

  if(heap_options_trace_free)
    if(setenv("LIBHEAP_TRACE_FREE", "1", 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_TRACE_FREE environment variable\n");
      exit(EXIT_FAILURE);
    }

  if(heap_options_trace_malloc)
    if(setenv("LIBHEAP_TRACE_MALLOC", "1", 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_TRACE_MALLOC environment variable\n");
      exit(EXIT_FAILURE);
    }

  if(heap_options_trace_calloc)
    if(setenv("LIBHEAP_TRACE_CALLOC", "1", 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_TRACE_CALLOC environment variable\n");
      exit(EXIT_FAILURE);
    }

  if(heap_options_trace_realloc)
    if(setenv("LIBHEAP_TRACE_REALLOC", "1", 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_TRACE_REALLOC environment variable\n");
      exit(EXIT_FAILURE);
    }

  if(heap_options_dumpdata)
    if(setenv("LIBHEAP_DUMPDATA", "1", 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_DUMPDATA environment variable\n");
      exit(EXIT_FAILURE);
    }

  if(heap_options_output)
    if(setenv("LIBHEAP_OUTPUT", heap_options_output, 0) == -1) {
      fprintf(stderr, "Can't set LIBHEAP_OUTPUT environment variable\n");
      exit(EXIT_FAILURE);
    }

  execvp(heap_options_command[0], heap_options_command);
}