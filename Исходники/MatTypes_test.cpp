TEST(MatTypesTest, transpose)
{
    Matrix4 M(Matrix4::Line(16, 2, 3, 13), Matrix4::Line(5, 11, 10, 8), Matrix4::Line(9, 7, 6, 12),
              Matrix4::Line(4, 14, 15, 1));

    Matrix4 Mnew;
    Mnew.transpose(M);

    Matrix4 Mtest(Matrix4::Line(16, 5, 9, 4), Matrix4::Line(2, 11, 7, 14), Matrix4::Line(3, 10, 6, 15),
                  Matrix4::Line(13, 8, 12, 1));

    EXPECT_EQ(Mnew, Mtest);
    EXPECT_EQ(M.transposed(), Mtest);

    M.transpose(M);
    EXPECT_EQ(M, Mtest);

    M = Matrix4(Matrix4::Line(16, 2, 3, 13), Matrix4::Line(5, 11, 10, 8), Matrix4::Line(9, 7, 6, 12),
              Matrix4::Line(4, 14, 15, 1));

    M.transpose();
    EXPECT_EQ(M, Mtest);

    M.identity();
    EXPECT_EQ(M.transposed(), M);
}