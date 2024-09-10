void TestIToA(void)
{
    char    sz[256];

    IToA(7, sz, 10);
    AssertString("7", sz);

    IToA(456, sz, 10);
    AssertString("456", sz);

    IToA(12, sz, 10);
    AssertString("12", sz);

    IToA(-1, sz, 10);
    AssertString("-1", sz);

    IToA(-32456, sz, 10);
    AssertString("-32456", sz);
}