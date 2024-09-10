 inline ExecStatus
 IteBnd<View>::post(Home home, BoolView b, View x0, View x1, View x2) {
   if (same(x0,x1) || b.one())
     return Rel::EqBnd<View,View>::post(home,x2,x0);
   if (b.zero())
     return Rel::EqBnd<View,View>::post(home,x2,x1);
   GECODE_ME_CHECK(x2.lq(home,std::max(x0.max(),x1.max())));
   GECODE_ME_CHECK(x2.gq(home,std::min(x0.min(),x1.min())));
   (void) new (home) IteBnd<View>(home,b,x0,x1,x2);
   return ES_OK;
 }