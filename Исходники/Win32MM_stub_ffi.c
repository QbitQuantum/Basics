void* prim_globalHandle(void * arg1)
{ static struct {HsPtr res1;HsInt gc_failed;HsPtr gc_failstring;} gc_result;
  HGLOBAL res1;int gc_failed;
	       char* gc_failstring;
  do {res1 = GlobalHandle(arg1);
      if ((gc_failed = ( res1==NULL ))) {gc_failstring = ErrorWin("GlobalHandle") ;}
      else {gc_failed = 0;}
      gc_result.res1 = (HGLOBAL)(res1);
      gc_result.gc_failed = gc_failed;
      gc_result.gc_failstring = gc_failstring;
      
      return(&gc_result);} while(0);
}