// Round::evaluate()
TEST(Round, evaluate_simple) {
    // Setup
    Constant* x = new Constant(0.9);
    Round* round = new Round(x);

    // Assertion
    EXPECT_TRUE(round->evaluate() == 1);

    // Clean up
    delete(round);
}