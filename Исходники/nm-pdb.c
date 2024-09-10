int main(int argc, char *argv[]) {
  DWORD  error;
  HANDLE process;
  ULONG64 module_base;
  SYM_CONTEXT ctx;
  int i;
  char* search;
  char* filename = NULL;
  int rv = 0;
  /* We may add SYMOPT_UNDNAME if --demangle is specified: */
  DWORD symopts = SYMOPT_DEFERRED_LOADS | SYMOPT_DEBUG;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--demangle") == 0 || strcmp(argv[i], "-C") == 0) {
      symopts |= SYMOPT_UNDNAME;
    } else if (strcmp(argv[i], "--help") == 0) {
      usage();
      exit(0);
    } else {
      break;
    }
  }
  if (i != argc - 1) {
    usage();
    exit(1);
  }
  filename = argv[i];

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

  ShowSymbolInfo(process, module_base);

  memset(&ctx, 0, sizeof(ctx));
  ctx.module_base = module_base;
  if (!SymEnumSymbols(process, module_base, NULL, EnumSymProc, &ctx)) {
    error = GetLastError();
    fprintf(stderr, "SymEnumSymbols returned error: %d\n", error);
    rv = 1;
  } else {
    DWORD j;
    qsort(ctx.syms, ctx.syms_len, sizeof(ctx.syms[0]), sym_cmp);
    for (j = 0; j < ctx.syms_len; j++) {
      printf("%016I64x X %s\n", ctx.syms[j].addr, ctx.syms[j].name);
    }
    /* In a perfect world, maybe we'd clean up ctx's memory? */
  }
  SymUnloadModule64(process, module_base);
  SymCleanup(process);
  return rv;
}