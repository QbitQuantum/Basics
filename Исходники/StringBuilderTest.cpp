TEST(StringBuilderTest, ToAtomicString)
{
    StringBuilder builder;
    builder.append("123");
    AtomicString atomicString = builder.toAtomicString();
    EXPECT_EQ(String("123"), atomicString);

    builder.reserveCapacity(256);
    EXPECT_TRUE(builder.canShrink());
    for (int i = builder.length(); i < 128; i++)
        builder.append('x');
    AtomicString atomicString1 = builder.toAtomicString();
    EXPECT_EQ(128u, atomicString1.length());
    EXPECT_EQ('x', atomicString1[127]);

    // Later change of builder should not affect the atomic string.
    for (int i = builder.length(); i < 256; i++)
        builder.append('x');
    EXPECT_EQ(128u, atomicString1.length());

    EXPECT_FALSE(builder.canShrink());
    String string = builder.toString();
    AtomicString atomicString2 = builder.toAtomicString();
    // They should share the same StringImpl.
    EXPECT_EQ(atomicString2.impl(), string.impl());
}