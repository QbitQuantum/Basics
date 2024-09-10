 ExecStatus
 ReLeFloat<View,CtrlView,rm>::post(Home home, View x, FloatVal c, CtrlView b) {
   if (b.one()) {
     if (rm != RM_PMI)
     {
       GECODE_ME_CHECK(x.lq(home,c.max()));
       if (x.assigned() && (x.max() >= c.min()))
         return ES_FAILED;
       (void) new (home) ReLeFloat<View,CtrlView,rm>(home,x,c,b);
     }
   } else if (b.zero()) {
     if (rm != RM_IMP)
       GECODE_ME_CHECK(x.gq(home,c.min()));
   } else {
     switch (rtest_le(x,c)) {
     case RT_TRUE:
       if (rm != RM_IMP)
         GECODE_ME_CHECK(b.one(home));
       break;
     case RT_FALSE:
       if (rm != RM_PMI)
         GECODE_ME_CHECK(b.zero(home));
       break;
     case RT_MAYBE:
       (void) new (home) ReLeFloat<View,CtrlView,rm>(home,x,c,b);
       break;
     default: GECODE_NEVER;
     }
   }
   return ES_OK;
 }