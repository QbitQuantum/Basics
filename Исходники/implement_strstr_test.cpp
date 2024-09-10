TEST(StrstrTestCase, InvaidInput)
{
    const char* haystack = "hello world";
    const char* needle = "world";

    EXPECT_EQ(NULL, strStr(NULL, NULL));
    EXPECT_EQ(NULL, strStr(NULL, needle));
    EXPECT_EQ(haystack, strStr(haystack, NULL));
    EXPECT_EQ(NULL, strStr("haha", "hahaha"));
}