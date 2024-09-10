TEST(TestHashMapRemove, addedItemThenRemoveItemHashMapShouldHave0items)
{
    HashMap Test;
    Test.add("Ford", "Tang");
    Test.remove("Ford");
    ASSERT_EQ(0, Test.size());
}