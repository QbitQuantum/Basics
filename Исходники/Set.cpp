 SetVar::SetVar(Space& home, const IntSet& glb,int ubMin,int ubMax,
                unsigned int minCard, unsigned int maxCard)
   : VarImpVar<Set::SetVarImp>(new (home) Set::SetVarImp(home,glb,ubMin,ubMax,
                                                         minCard,maxCard)) {
   Set::Limits::check(glb,"SetVar::SetVar");
   Set::Limits::check(ubMin,"SetVar::SetVar");
   Set::Limits::check(ubMax,"SetVar::SetVar");
   Set::Limits::check(maxCard,"SetVar::SetVar");
   if (minCard > maxCard || minCard > lubSize() || maxCard < glbSize() ||
       glb.min() < ubMin || glb.max() > ubMax)
     throw Set::VariableEmptyDomain("SetVar::SetVar");
 }