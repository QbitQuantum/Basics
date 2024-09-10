TEST_F(QuaternionTest, sperical_linear_interpolation_makes_correct_quaternion)
{
    auto from = create_random_quaternion();
    auto to = create_random_quaternion();
    quaternion_normalize(from);
    quaternion_normalize(to);

    const auto t =(rand() % 400) / 400.0;
    const auto res = quaternion_slerp(from, to, t);
    const auto correct = slerp(from, to, t);

    EXPECT_EQ(correct.w(), res.w());
    EXPECT_EQ(correct.x(), res.x());
    EXPECT_EQ(correct.y(), res.y());
    EXPECT_EQ(correct.z(), res.z());
}