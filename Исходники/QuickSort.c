int partition(int *a, int lo, int hi)
  //@ requires a[lo..hi + 1] |-> ?vs &*& lo <= hi;
  /*@
  ensures
      a[lo..result] |-> ?vslow &*&
      a[result] |-> ?vpivot &*&
      a[result + 1..hi + 1] |-> ?vshigh &*&
      forall(vslow, (ge)(vpivot)) == true &*&
      forall(vshigh, (le)(vpivot)) == true &*&
      (mplus)((count_eq)(vslow), (count_eq)(cons(vpivot, vshigh))) == (count_eq)(vs);
  @*/
{
  //@ ints_split(a + lo, hi - lo);
  int pivot = *(a+hi);
  //@ assert a[lo..hi] |-> ?vstodo0 &*& a[hi..hi + 1] |-> cons(_, ?vsrest);
  //@ switch (vsrest) { case nil: case cons(h, t): }
  int i = lo - 1;
  int j;
  //@ count_eq_append(vstodo0, {pivot});
  //@ assert vs == append(vstodo0, {pivot});
  for (j = lo; j < hi; j++)
    /*@
    invariant
      a[lo..i + 1] |-> ?vslow &*&
      a[i + 1..j] |-> ?vshigh &*&
      a[j..hi] |-> ?vstodo &*&
      forall(vslow, (ge)(pivot)) == true &*&
      forall(vshigh, (le)(pivot)) == true &*&
      (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh)))) == (count_eq)(vs);
    @*/
  {
    
    int aj = *(a + j);
    if (aj < pivot) {
      i++;
      if (i < j) {
        swap(a, i, j);
        //@ int ai = a[j];
        //@ close ints(a + i, 1, {aj});
        //@ ints_join(a + lo);
        //@ close ints(a + j, 1, {ai});
        //@ ints_join(a + i + 1);
        //@ forall_append(vslow, {aj}, (ge)(pivot));
        //@ forall_append(tail(vshigh), {ai}, (le)(pivot));
        /*@
        if ((mplus)((count_eq)(tail(vstodo)), (mplus)((count_eq)(append(vslow, {aj})), (count_eq)(cons(pivot, append(tail(vshigh), {ai}))))) !=
            (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh))))) {
            int x = fixpoint_neq_elim((mplus)((count_eq)(tail(vstodo)), (mplus)((count_eq)(append(vslow, {aj})), (count_eq)(cons(pivot, append(tail(vshigh), {ai}))))),
                                    (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh)))));
            count_append(vslow, {aj}, (eq)(x));
            count_append(tail(vshigh), {ai}, (eq)(x));
            assert false;
        }
        @*/
      } else {
        //@ assert i == j;
        //@ open ints(a + i, 0, _);
        //@ close ints(a + i, 1, _);
        //@ ints_join(a + lo);
        //@ forall_append(vslow, {aj}, (ge)(pivot));
        /*@
        if ((mplus)((count_eq)(tail(vstodo)), (mplus)((count_eq)(append(vslow, {aj})), (count_eq)({pivot}))) !=
            (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh))))) {
            int x = fixpoint_neq_elim((mplus)((count_eq)(tail(vstodo)), (mplus)((count_eq)(append(vslow, {aj})), (count_eq)({pivot}))),
                                    (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh)))));
            count_append(vslow, {aj}, (eq)(x));
            assert false;
        }
        @*/
      }
    } else {
      //@ close ints(a + j, 1, {aj});
      //@ ints_join(a + i + 1);
      //@ forall_append(vshigh, {aj}, (le)(pivot));
      /*@
      if ((mplus)((count_eq)(tail(vstodo)), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, append(vshigh, {aj}))))) !=
          (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh))))) {
          int x = fixpoint_neq_elim((mplus)((count_eq)(tail(vstodo)), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, append(vshigh, {aj}))))),
                                  (mplus)((count_eq)(vstodo), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh)))));
          count_append(vshigh, {aj}, (eq)(x));
          assert false;
      }
      @*/
    }
  }
  //@ assert j == hi;
  //@ open ints(a + hi, 0, _);
  i++;
  //@ assert a[lo..i] |-> ?vslow &*& a[i..hi] |-> ?vshigh;
  if (i < hi) {
    swap(a, i, hi);
    //@ int ai = a[hi];
    //@ close ints(a + hi, 1, {ai});
    //@ ints_join(a + i + 1);
    //@ forall_append(tail(vshigh), {ai}, (le)(pivot));
      /*@
      if ((mplus)((count_eq)(vslow), (count_eq)(cons(pivot, append(tail(vshigh), {ai})))) !=
          (mplus)((count_eq)(nil), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh))))) {
          int x = fixpoint_neq_elim((mplus)((count_eq)(vslow), (count_eq)(cons(pivot, append(tail(vshigh), {ai})))),
                                  (mplus)((count_eq)(nil), (mplus)((count_eq)(vslow), (count_eq)(cons(pivot, vshigh)))));
          count_append(tail(vshigh), {ai}, (eq)(x));
          assert false;
      }
      @*/
  } else {
      //@ assert i == hi;
      //@ open ints(a + hi, 0, _);
  }
  return i;
}