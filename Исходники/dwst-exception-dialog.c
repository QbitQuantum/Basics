static void dlgPrint(
    uint64_t addr,const char *filename,int lineno,const char *funcname,
    void *context,int columnno )
{
  struct dialog_info *di = context;
#ifndef NO_DBGHELP
  char buffer[sizeof(SYMBOL_INFO)+MAX_SYM_NAME];
  SYMBOL_INFO *si = (SYMBOL_INFO*)&buffer;
  if( lineno==DWST_NO_DBG_SYM )
  {
    IMAGEHLP_LINE64 ihl;
    memset( &ihl,0,sizeof(IMAGEHLP_LINE64) );
    ihl.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    DWORD displ;
    if( SymGetLineFromAddr64(GetCurrentProcess(),addr,&displ,&ihl) )
    {
      filename = ihl.FileName;
      lineno = ihl.LineNumber;
    }

    DWORD64 displ2;
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = MAX_SYM_NAME;
    if( SymFromAddr(GetCurrentProcess(),addr,&displ2,si) )
    {
      char *fn = si->Name;
      fn[MAX_SYM_NAME] = 0;
      funcname = fn;
    }
  }
#endif

  const char *delim = strrchr( filename,'/' );
  if( delim ) filename = delim + 1;
  delim = strrchr( filename,'\\' );
  if( delim ) filename = delim + 1;

  void *ptr = (void*)(uintptr_t)addr;
  switch( lineno )
  {
    case DWST_BASE_ADDR:
      if( ptr==di->lastBase ) break;
      di->lastBase = ptr;

      printAddr( di->hwnd,TEXT("base address"),-1,
          ptr,filename,0,NULL,0 );
      break;

    case DWST_NOT_FOUND:
    case DWST_NO_DBG_SYM:
    case DWST_NO_SRC_FILE:
      printAddr( di->hwnd,TEXT("    stack "),di->count++,
          ptr,NULL,0,funcname,0 );
      break;

    default:
      printAddr( di->hwnd,TEXT("    stack "),di->count,
          ptr,filename,lineno,funcname,columnno );
      if( ptr ) di->count++;
      break;
  }
}