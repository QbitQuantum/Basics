TEST(RoundTest, MasterWins) {

    // MockMaster always evaluates with no blacks and no whites
    class MockMaster : public Master {
    public:
        Key getKey(const Code &code) {
            return Key(0, 0);
        }
    };

    MockMaster master = MockMaster();
    MockBreaker breaker = MockBreaker();
    Round round = Round(master, breaker);

    bool breakerWins = round.play();

    // Master wins after 12 rounds
    ASSERT_FALSE(breakerWins);
    ASSERT_EQ(MAX_TURNS_PER_ROUND - 1, round.getTurn());
}