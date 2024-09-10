  void test_remove_redistributes() {
    size_t bins = tbl-> bins()->to_native();
    size_t bound = bins * 2;

    for(size_t i = 0; i < bound; i++) {
      tbl->store(state, Fixnum::from(i), cTrue);
    }

    TS_ASSERT(bins < (size_t)tbl-> bins()->to_native());

    for(size_t i = 0; i < bound; i++) {
      Object* out = tbl->remove(state, Fixnum::from(i));
      TS_ASSERT_EQUALS(out, cTrue);
    }

    TS_ASSERT_EQUALS(bins, static_cast<unsigned int>(tbl-> bins()->to_native()));
  }