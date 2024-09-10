PTABDEF OEMDEF::GetXdef(PGLOBAL g)
  {
  typedef PTABDEF (__stdcall *XGETDEF) (PGLOBAL, void *);
  char    c, getname[40] = "Get";
  PTABDEF xdefp;
  XGETDEF getdef = NULL;
  PCATLG  cat = Cat;

#if defined(WIN32)
  // Is the DLL already loaded?
  if (!Hdll && !(Hdll = GetModuleHandle(Module)))
    // No, load the Dll implementing the function
    if (!(Hdll = LoadLibrary(Module))) {
      char  buf[256];
      DWORD rc = GetLastError();

      sprintf(g->Message, MSG(DLL_LOAD_ERROR), rc, Module);
      FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS, NULL, rc, 0,
                    (LPTSTR)buf, sizeof(buf), NULL);
      strcat(strcat(g->Message, ": "), buf);
      return NULL;
      } // endif hDll

  // The exported name is always in uppercase
  for (int i = 0; ; i++) {
    c = Subtype[i];
    getname[i + 3] = toupper(c);
    if (!c) break;
    } // endfor i

  // Get the function returning an instance of the external DEF class
  if (!(getdef = (XGETDEF)GetProcAddress((HINSTANCE)Hdll, getname))) {
    sprintf(g->Message, MSG(PROCADD_ERROR), GetLastError(), getname);
    FreeLibrary((HMODULE)Hdll);
    return NULL;
    } // endif getdef
#else   // !WIN32
  const char *error = NULL;
  // Is the library already loaded?
//  if (!Hdll && !(Hdll = ???))
  // Load the desired shared library
  if (!(Hdll = dlopen(Module, RTLD_LAZY))) {
    error = dlerror();
    sprintf(g->Message, MSG(SHARED_LIB_ERR), Module, SVP(error));
    return NULL;
    } // endif Hdll

  // The exported name is always in uppercase
  for (int i = 0; ; i++) {
    c = Subtype[i];
    getname[i + 3] = toupper(c);
    if (!c) break;
    } // endfor i

  // Get the function returning an instance of the external DEF class
  if (!(getdef = (XGETDEF)dlsym(Hdll, getname))) {
    error = dlerror();
    sprintf(g->Message, MSG(GET_FUNC_ERR), getname, SVP(error));
    dlclose(Hdll);
    return NULL;
    } // endif getdef
#endif  // !WIN32

  // Just in case the external Get function does not set error messages
  sprintf(g->Message, MSG(DEF_ALLOC_ERROR), Subtype);

  // Get the table definition block
  if (!(xdefp = getdef(g, NULL)))
    return NULL;

  // Have the external class do its complete definition
  if (!cat->Cbuf) {
    // Suballocate a temporary buffer for the entire column section
    cat->Cblen = cat->GetSizeCatInfo("Colsize", "8K");
    cat->Cbuf = (char*)PlugSubAlloc(g, NULL, cat->Cblen);
    } // endif Cbuf

  // Here "OEM" should be replace by a more useful value
  if (xdefp->Define(g, cat, Name, "OEM"))
    return NULL;

  // Ok, return external block
  return xdefp;
  } // end of GetXdef