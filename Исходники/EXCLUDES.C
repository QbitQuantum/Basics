void FreeExcludes (char ***ex,int *nex) {

  int x;

  if(ex && *ex) {
    for(x = 0;(*ex)[x];x++)
      free((*ex)[x]);
    free(*ex);
    _heapmin();
  }
  if(nex)
    *nex = 0;
  if(ex)
    *ex = NULL;
}