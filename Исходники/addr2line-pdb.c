int main(int argc, char *argv[]) {
  DWORD  error;
  HANDLE process;
  ULONG64 module_base;
  int i;
  char* search;
  char buf[256];   /* Enough to hold one hex address, I trust! */
  int rv = 0;
  /* We may add SYMOPT_UNDNAME if --demangle is specified: */
  DWORD symopts = SYMOPT_DEFERRED_LOADS | SYMOPT_DEBUG | SYMOPT_LOAD_LINES;
  char* filename = "a.out";         /* The default if -e isn't specified */
  int print_function_name = 0;      /* Set to 1 if -f is specified */

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--functions") == 0 || strcmp(argv[i], "-f") == 0) {
      print_function_name = 1;
    } else if (strcmp(argv[i], "--demangle") == 0 ||
               strcmp(argv[i], "-C") == 0) {
      symopts |= SYMOPT_UNDNAME;
    } else if (strcmp(argv[i], "-e") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "FATAL ERROR: -e must be followed by a filename\n");
        return 1;
      }
      filename = argv[i+1];
      i++;     /* to skip over filename too */
    } else if (strcmp(argv[i], "--help") == 0) {
      usage();
      exit(0);
    } else {
      usage();
      exit(1);
    }
  }

  process = GetCurrentProcess();

  if (!SymInitialize(process, NULL, FALSE)) {
    error = GetLastError();
    fprintf(stderr, "SymInitialize returned error : %d\n", error);
    return 1;
  }

  search = malloc(SEARCH_CAP);
  if (SymGetSearchPath(process, search, SEARCH_CAP)) {
    if (strlen(search) + sizeof(";" WEBSYM) > SEARCH_CAP) {
      fprintf(stderr, "Search path too long\n");
      SymCleanup(process);
      return 1;
    }
    strcat(search, ";" WEBSYM);
  } else {
    error = GetLastError();
    fprintf(stderr, "SymGetSearchPath returned error : %d\n", error);
    rv = 1;                   /* An error, but not a fatal one */
    strcpy(search, WEBSYM);   /* Use a default value */
  }
  if (!SymSetSearchPath(process, search)) {
    error = GetLastError();
    fprintf(stderr, "SymSetSearchPath returned error : %d\n", error);
    rv = 1;                   /* An error, but not a fatal one */
  }

  SymSetOptions(symopts);
  module_base = SymLoadModuleEx(process, NULL, filename, NULL, 0, 0, NULL, 0);
  if (!module_base) {
    /* SymLoadModuleEx failed */
    error = GetLastError();
    fprintf(stderr, "SymLoadModuleEx returned error : %d for %s\n",
            error, filename);
    SymCleanup(process);
    return 1;
  }

  buf[sizeof(buf)-1] = '\0';  /* Just to be safe */
  while (fgets(buf, sizeof(buf)-1, stdin)) {
    /* GNU addr2line seems to just do a strtol and ignore any
     * weird characters it gets, so we will too.
     */
    unsigned __int64 addr = _strtoui64(buf, NULL, 16);
    ULONG64 buffer[(sizeof(SYMBOL_INFO) +
                    MAX_SYM_NAME*sizeof(TCHAR) +
                    sizeof(ULONG64) - 1)
                   / sizeof(ULONG64)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
    IMAGEHLP_LINE64 line;
    DWORD dummy;
    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    pSymbol->MaxNameLen = MAX_SYM_NAME;
    if (print_function_name) {
      if (SymFromAddr(process, (DWORD64)addr, NULL, pSymbol)) {
        printf("%s\n", pSymbol->Name);
      } else {
        printf("??\n");
      }
    }
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    if (SymGetLineFromAddr64(process, (DWORD64)addr, &dummy, &line)) {
      printf("%s:%d\n", line.FileName, (int)line.LineNumber);
    } else {
      printf("??:0\n");
    }
  }
  SymUnloadModule64(process, module_base);
  SymCleanup(process);
  return rv;
}