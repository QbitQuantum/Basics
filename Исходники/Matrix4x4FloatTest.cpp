TEST_F(Matrix4x4FloatTest, inverse)
{
    Matrix4x4<FLOAT> inv;

    // Identity inverse
    Matrix4x4<FLOAT> m;

    inv = m.inverse();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(Matrix4x4<FLOAT>::IDENTITY[i], m[i]);
    }

    // General inverse
    Matrix4x4<FLOAT> n(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                      -1,   1,   3,  2);

    inv = n.inverse();

    Matrix4x4<FLOAT> res(0.276413, -0.144717, -0.0983526, 1.73464,
                        0.187629, -0.162474, -0.0674756, 1.41373,
                        0.0118378, 0.00236756, -0.0263392, 0.398343,
                        0.0266351, 0.00532702, 0.0240702, 0.0629378);

    EXPECT_NEAR(res[ 0], inv[ 0], 1e-6);
    EXPECT_NEAR(res[ 1], inv[ 1], 1e-6);
    EXPECT_NEAR(res[ 2], inv[ 2], 1e-7);
    EXPECT_NEAR(res[ 3], inv[ 3], 1e-7);
    EXPECT_NEAR(res[ 4], inv[ 4], 1e-6);
    EXPECT_NEAR(res[ 5], inv[ 5], 1e-6);
    EXPECT_NEAR(res[ 6], inv[ 6], 1e-7);
    EXPECT_NEAR(res[ 7], inv[ 7], 1e-7);
    EXPECT_NEAR(res[ 8], inv[ 8], 1e-7);
    EXPECT_NEAR(res[ 9], inv[ 9], 1e-7);
    EXPECT_NEAR(res[10], inv[10], 1e-7);
    EXPECT_NEAR(res[11], inv[11], 1e-7);
    EXPECT_NEAR(res[12], inv[12], 1e-5);
    EXPECT_NEAR(res[13], inv[13], 1e-5);
    EXPECT_NEAR(res[14], inv[14], 1e-6);
    EXPECT_NEAR(res[15], inv[15], 1e-7);

    // Affine inverse
    Matrix4x4<FLOAT> o(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                       0,   0,   0,  1);

    inv = o.inverse();

    Matrix4x4<FLOAT> resaff(-0.45768, -0.291536, -0.761755, 27.5611,
                           -0.410658, -0.282132, -0.60815, 22.4624,
                           -0.15674, -0.031348, -0.178683, 6.32915,
                            0,        0,         0,        1);

    EXPECT_NEAR(resaff[ 0], inv[ 0], 1e-6);
    EXPECT_NEAR(resaff[ 1], inv[ 1], 1e-6);
    EXPECT_NEAR(resaff[ 2], inv[ 2], 1e-6);
    EXPECT_NEAR(resaff[ 3], inv[ 3], 1e-7);
    EXPECT_NEAR(resaff[ 4], inv[ 4], 1e-7);
    EXPECT_NEAR(resaff[ 5], inv[ 5], 1e-6);
    EXPECT_NEAR(resaff[ 6], inv[ 6], 1e-7);
    EXPECT_NEAR(resaff[ 7], inv[ 7], 1e-7);
    EXPECT_NEAR(resaff[ 8], inv[ 8], 1e-6);
    EXPECT_NEAR(resaff[ 9], inv[ 9], 1e-6);
    EXPECT_NEAR(resaff[10], inv[10], 1e-6);
    EXPECT_NEAR(resaff[11], inv[11], 1e-7);
    EXPECT_NEAR(resaff[12], inv[12], 1e-4);
    EXPECT_NEAR(resaff[13], inv[13], 1e-4);
    EXPECT_NEAR(resaff[14], inv[14], 1e-5);
    EXPECT_NEAR(resaff[15], inv[15], 1e-7);
}