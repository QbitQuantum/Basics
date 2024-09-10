TEST_F(AlignTest, SequenceTestInital) {
    sc->initial_sequences();

    std::vector<std::vector<int>> expected_sequence = {
        { 8, 19,
          9, 20 },
        { 10, 21,
          12, 22 },
        { 12, 27,
          13, 28 }
    };

    // put actual indexes values into array too
    Align::Hypothesis *result = sc->get_result();
    Align::Hypothesis::iterator seq = result->begin();
    int exp = 0;
    while (seq != result->end()) {
        EXPECT_EQ(expected_sequence[exp], std::vector<int>(**seq));
        ++seq;
        ++exp;
    }
}