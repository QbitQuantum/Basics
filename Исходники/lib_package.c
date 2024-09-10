static const char *ll_bcsym(void *lib, const char *sym)
{
  if (lib) {
    return (const char *)GetProcAddress((HINSTANCE)lib, sym);
  } else {
    HINSTANCE h = GetModuleHandleA(NULL);
    const char *p = (const char *)GetProcAddress(h, sym);
    if (p == NULL && GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
					(const char *)ll_bcsym, &h))
      p = (const char *)GetProcAddress(h, sym);
    return p;
  }
}