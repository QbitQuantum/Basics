TEST(AgradRevMatrix, sdStdVector) {
    using stan::math::sd; // should use arg-dep lookup (and for sqrt)

    AVEC y1 = createAVEC(0.5,2.0,3.5);
    AVAR f1 = sd(y1);
    VEC grad1 = cgrad(f1, y1[0], y1[1], y1[2]);
    double f1_val = f1.val(); // save before cleaned out

    AVEC y2 = createAVEC(0.5,2.0,3.5);
    AVAR mean2 = (y2[0] + y2[1] + y2[2]) / 3.0;
    AVAR sum_sq_diff_2
        = (y2[0] - mean2) * (y2[0] - mean2)
          + (y2[1] - mean2) * (y2[1] - mean2)
          + (y2[2] - mean2) * (y2[2] - mean2);
    AVAR f2 = sqrt(sum_sq_diff_2 / (3 - 1));

    EXPECT_EQ(f2.val(), f1_val);

    VEC grad2 = cgrad(f2, y2[0], y2[1], y2[2]);

    EXPECT_EQ(3U, grad1.size());
    EXPECT_EQ(3U, grad2.size());
    for (size_t i = 0; i < 3; ++i)
        EXPECT_FLOAT_EQ(grad2[i], grad1[i]);
}