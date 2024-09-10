void ProxyPatch::setSpanningTree(int p, int *c, int n) { 
#if CMK_PERSISTENT_COMM && USE_PERSISTENT_TREE && ! defined(USE_NODEPATCHMGR)
  if (ntreephs!=0) {
      for (int i=0; i<ntreephs; i++)  CmiDestoryPersistent(treephs[i]);
      delete [] treephs;
  }
  treephs = NULL;
  if (n) {
      treephs = new PersistentHandle[n];
      for (int i=0; i<n; i++) {
           treephs[i] = CmiCreatePersistent(c[i], 27000, sizeof(envelope)+sizeof(ProxyDataMsg));
      }
  }
  ntreephs = n;
#endif
  parent=p; nChild = n; nWait = 0;
  delete [] child;
  if(n==0) {
      child = NULL;
      return;
  }
  child = new int[n];
  for (int i=0; i<n; i++) child[i] = c[i];

  #if defined(PROCTRACE_DEBUG) && defined(NAST_DEBUG)
    DebugFileTrace *dft = DebugFileTrace::Object();
    dft->openTrace();
    dft->writeTrace("ProxyPatch[%d] has %d children: ", patchID, nChild);
    for(int i=0; i<nChild; i++)
        dft->writeTrace("%d ", child[i]);
    dft->writeTrace("\n");
    dft->closeTrace();
  #endif
//CkPrintf("setSpanningTree: [%d:%d] %d %d:%d %d\n", CkMyPe(), patchID, parent, nChild, child[0], child[1]);
}