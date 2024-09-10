 IntVar::IntVar(Space& home, const IntSet& ds)
   : VarImpVar<Int::IntVarImp>(new (home) Int::IntVarImp(home,ds)) {
   Int::Limits::check(ds.min(),"IntVar::IntVar");
   Int::Limits::check(ds.max(),"IntVar::IntVar");
   if (ds.size() == 0)
     throw Int::VariableEmptyDomain("IntVar::IntVar");
 }