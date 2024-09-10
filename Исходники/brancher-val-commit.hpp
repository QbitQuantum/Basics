 forceinline ModEvent
 ValCommitFunction<View>::commit(Space& home, unsigned int a, View x, int i, 
                                 Val n) {
   typename View::VarType y(x.varimp());
   c(home,a,y,i,n);
   return home.failed() ? ES_FAILED : ES_OK;
 }