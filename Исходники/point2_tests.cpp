TEST(Point2, SetMethods) {
    Point2F pt;
    pt.set(4.f, 2.f);
    EXPECT_FLOAT_EQ(4.f, pt.x);
    EXPECT_FLOAT_EQ(2.f, pt.y);

    auto lst = {0.f, 5.f};
    pt.set(lst);
    EXPECT_FLOAT_EQ(0.f, pt.x);
    EXPECT_FLOAT_EQ(5.f, pt.y);

    pt.set(Point2F(9.f, 8.f));
    EXPECT_FLOAT_EQ(9.f, pt.x);
    EXPECT_FLOAT_EQ(8.f, pt.y);
}