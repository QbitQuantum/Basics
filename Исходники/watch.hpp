 ExecStatus
 Watch<View>::post(Home home, View x0, View x1, unsigned int _x0Size) {
   if (x0.size() != _x0Size) {
     return ES_FAILED;
   } else if (x1.assigned()) {
     GECODE_ME_CHECK(x0.eq(home,x1.val()));
   } else {
     assert(!same(x0,x1));
     GECODE_ME_CHECK(x0.lq(home,x1.max()));
     GECODE_ME_CHECK(x1.lq(home,x0.max()));
     GECODE_ME_CHECK(x0.gq(home,x1.min()));
     GECODE_ME_CHECK(x1.gq(home,x0.min()));
     assert(x0.size() == x1.size());
     (void) new (home) Watch<View>(home,x0,x1,_x0Size);
   }
   return ES_OK;
 }