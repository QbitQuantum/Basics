TEST(StringBuilderTest, Resize)
{
    StringBuilder builder;
    builder.append("0123456789");
    builder.resize(10);
    EXPECT_EQ(10U, builder.length());
    expectBuilderContent("0123456789", builder);
    builder.resize(8);
    EXPECT_EQ(8U, builder.length());
    expectBuilderContent("01234567", builder);

    builder.toString();
    builder.resize(7);
    EXPECT_EQ(7U, builder.length());
    expectBuilderContent("0123456", builder);
    builder.resize(0);
    expectEmpty(builder);
}