  void test_div() {
    Fixnum* one = as<Fixnum>(Fixnum::from(4));

    Fixnum* two = as<Fixnum>(one->div(state, one));
    TS_ASSERT_EQUALS(two->to_native(), 1);

    Fixnum* zero = Fixnum::from(0);
    TS_ASSERT_THROWS_ASSERT(one->div(state, zero), const RubyException &e,
                            TS_ASSERT(Exception::zero_division_error_p(state, e.exception)));
  }