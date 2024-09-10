// Lerp Tests
TEST_F(BBoxTest, LerpZeroOneWorks) {
    BBox b (Point (0, 0, 0), Point (1, 1, 1));

    Point p = b.Lerp (1, 1, 1);

    EXPECT_EQ (1, p.x);
    EXPECT_EQ (1, p.y);
    EXPECT_EQ (1, p.z);
}