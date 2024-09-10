void TestAllocator(Allocator& a) {
    EXPECT_TRUE(a.Malloc(0) == 0);

    uint8_t* p = (uint8_t*)a.Malloc(100);
    EXPECT_TRUE(p != 0);
    for (size_t i = 0; i < 100; i++)
        p[i] = (uint8_t)i;

    // Expand
    uint8_t* q = (uint8_t*)a.Realloc(p, 100, 200);
    EXPECT_TRUE(q != 0);
    for (size_t i = 0; i < 100; i++)
        EXPECT_EQ(i, q[i]);
    for (size_t i = 100; i < 200; i++)
        q[i] = (uint8_t)i;

    // Shrink
    uint8_t *r = (uint8_t*)a.Realloc(q, 200, 150);
    EXPECT_TRUE(r != 0);
    for (size_t i = 0; i < 150; i++)
        EXPECT_EQ(i, r[i]);

    Allocator::Free(r);

    // Realloc to zero size
    EXPECT_TRUE(a.Realloc(a.Malloc(1), 1, 0) == 0);
}