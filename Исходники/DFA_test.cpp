TEST_F(TestDFA, RValueOperations) {
    DFA first;
    first << "q0" << "q1" << "q2";
    first.addTransition("q0", "q1", 'a');
    first.addTransition("q1", "q2", 'a');
    first.addTransition("q2", "q0", 'a');
    first.accept("q0");

    DFA second;
    second << "q0" << "q1";
    second.addTransition("q0", "q1", 'a');
    second.addTransition("q1", "q0", 'a');
    second.accept("q1");

    EXPECT_NO_THROW(first & ~second);
    EXPECT_NO_THROW(first | ~second);
    EXPECT_NO_THROW(first == ~second);
    EXPECT_NO_THROW(first.contains(~second));
    EXPECT_NO_THROW(second.contains(~first));
}