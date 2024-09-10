 ExecStatus
 ReIntSet<View,rm>::post(Home home, View x, const IntSet& s, BoolView b) {
   if (s.ranges() == 0) {
     if (rm == RM_PMI)
       return ES_OK;
     GECODE_ME_CHECK(b.zero(home));
   } else if (s.ranges() == 1) {
     return ReRange<View,rm>::post(home,x,s.min(),s.max(),b);
   } else if (b.one()) {
     if (rm == RM_PMI)
       return ES_OK;
     IntSetRanges i_is(s);
     GECODE_ME_CHECK(x.inter_r(home,i_is,false));
   } else if (b.zero()) {
     if (rm == RM_IMP)
       return ES_OK;
     IntSetRanges i_is(s);
     GECODE_ME_CHECK(x.minus_r(home,i_is,false));
   } else {
     (void) new (home) ReIntSet<View,rm>(home,x,s,b);
   }
   return ES_OK;
 }