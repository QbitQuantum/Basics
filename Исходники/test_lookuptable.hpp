  void test_remove_works_for_unknown_key() {
    Object* k1 = Fixnum::from(4);

    TS_ASSERT_EQUALS(cNil, tbl->remove(state, k1));
  }