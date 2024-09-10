const void* rocs_lib_getProc( iOLib inst, const char* procname ) {
  void* proc = NULL;
#ifdef __ROCS_LIB__
  iOLibData o = Data(inst);
  proc = GetProcAddress( o->lh, procname );
  if( proc == NULL || IsBadCodePtr(proc) ) {
    TraceOp.trc( name, TRCLEVEL_EXCEPTION, __LINE__, 9999, "rocs_lib_getProc [%s:%s] failed. rc=%d", o->name, procname, GetLastError() );
    return NULL;
  }
  TraceOp.trc( name, TRCLEVEL_INFO, __LINE__, 9999, "rocs_lib_getProc OK [%s:%s]", o->name, procname );
#endif
  return proc;
}