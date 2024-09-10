TEST(WTF_HashSet, MoveOnly)
{
    HashSet<MoveOnly> hashSet;

    for (size_t i = 0; i < 100; ++i) {
        MoveOnly moveOnly(i + 1);
        hashSet.add(WTF::move(moveOnly));
    }

    for (size_t i = 0; i < 100; ++i)
        EXPECT_TRUE(hashSet.contains(MoveOnly(i + 1)));

    for (size_t i = 0; i < 100; ++i)
        EXPECT_TRUE(hashSet.remove(MoveOnly(i + 1)));

    EXPECT_TRUE(hashSet.isEmpty());

    for (size_t i = 0; i < 100; ++i)
        hashSet.add(MoveOnly(i + 1));

    for (size_t i = 0; i < 100; ++i)
        EXPECT_TRUE(hashSet.take(MoveOnly(i + 1)) == MoveOnly(i + 1));

    EXPECT_TRUE(hashSet.isEmpty());

    for (size_t i = 0; i < 100; ++i)
        hashSet.add(MoveOnly(i + 1));

    HashSet<MoveOnly> secondSet;

    for (size_t i = 0; i < 100; ++i)
        secondSet.add(hashSet.takeAny());

    EXPECT_TRUE(hashSet.isEmpty());

    for (size_t i = 0; i < 100; ++i)
        EXPECT_TRUE(secondSet.contains(MoveOnly(i + 1)));
}