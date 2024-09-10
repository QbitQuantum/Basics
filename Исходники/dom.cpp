 void
 dom(Home home, IntVar x, const IntSet& is, Reify r, IntConLevel) {
   using namespace Int;
   Limits::check(is.min(),"Int::dom");
   Limits::check(is.max(),"Int::dom");
   if (home.failed()) return;
   switch (r.mode()) {
   case RM_EQV:
     GECODE_ES_FAIL((Dom::ReIntSet<IntView,RM_EQV>::post(home,x,is,r.var())));
     break;
   case RM_IMP:
     GECODE_ES_FAIL((Dom::ReIntSet<IntView,RM_IMP>::post(home,x,is,r.var())));
     break;
   case RM_PMI:
     GECODE_ES_FAIL((Dom::ReIntSet<IntView,RM_PMI>::post(home,x,is,r.var())));
     break;
   default: throw UnknownReifyMode("Int::dom");
   }
 }