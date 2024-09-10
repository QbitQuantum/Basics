  void test_match_region_with_backward_captures() {
    String *pat = String::create(state, ".(.)");
    Regexp* re = Regexp::create(state);
    re->initialize(state, pat, Fixnum::from(0));

    String *input = String::create(state, "abc");

    Fixnum* start = Fixnum::from(0);
    Fixnum* end =   Fixnum::from(3);
    Object* forward = cFalse;

    MatchData* matches = re->match_region(state, input, start, end, forward);
    TS_ASSERT(!matches->nil_p());
    TS_ASSERT_EQUALS(as<Integer>(matches->full()->at(state, 0))->to_native(), 1);
    TS_ASSERT_EQUALS(as<Integer>(matches->full()->at(state, 1))->to_native(), 3);

    TS_ASSERT_EQUALS(matches->region()->num_fields(), 1);
    TS_ASSERT_EQUALS(as<Integer>(as<Tuple>(matches->region()->at(state, 0))->at(state, 0))->to_native(), 2);
    TS_ASSERT_EQUALS(as<Integer>(as<Tuple>(matches->region()->at(state, 0))->at(state, 1))->to_native(), 3);
  }