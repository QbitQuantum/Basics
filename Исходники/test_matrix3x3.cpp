TEST(Matrix3x3, Transform)
{
    Matrix3x3 position;
    position.transform(Vector2F(2.0f, 3.0f),
                       Vector2F(1.0f, 1.0f),
                       0.0,
                       Vector2F());
    Matrix3x3 exPosition(1.0f, 0.0f, 2.0f,
                         0.0f, 1.0f, 3.0f,
                         0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exPosition, position);

    Matrix3x3 pivot;
    pivot.transform(Vector2F(),
                    Vector2F(1.0f, 1.0f),
                    0.0,
                    Vector2F(2.0f, 3.0f));
    EXPECT_EQ(exPosition, pivot);

    Matrix3x3 rotation;
    rotation.transform(Vector2F(),
                       Vector2F(1.0f, 1.0f),
                       180.0,
                       Vector2F());
    Matrix3x3 exRotation(-1.0f, 0.0f, 0.0f,
                         0.0f, -1.0f, 0.0f,
                         0.0f,  0.0f, 1.0f);
    EXPECT_EQ(exRotation, rotation);

    Matrix3x3 scale;
    scale.transform(Vector2F(),
                    Vector2F(2.0f, 3.0f),
                    0.0,
                    Vector2F());
    Matrix3x3 exScale(2.0f, 0.0f, 0.0f,
                      0.0f, 3.0f, 0.0f,
                      0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exScale, scale);

    // NOTE: Matrix equality checks if the values are close. Because this
    // uses trig the rotation values do not line up to 0.0.
    Matrix3x3 all;
    all.transform(Vector2F(5.0f, 6.0f),
                  Vector2F(2.0f, 3.0f),
                  180.0,
                  Vector2F(10.0f, 20.0f));
    Matrix3x3 exAll(-2.0f, 0.0f,  -15.0f,
                    0.0f,  -3.0f, -54.0f,
                    0.0f,  0.0f,  1.0f);
    EXPECT_EQ(exAll, all);
}