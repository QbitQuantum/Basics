TEST(VecTest, vec3fDistanceTo) {
    const Vec3f v1(2.3f, 8.7878f, -2323.0f);
    const Vec3f v2(4.333f, -2.0f, 322.0f);
    ASSERT_FLOAT_EQ(0.0f, v1.distanceTo(v1));
    ASSERT_FLOAT_EQ(v1.length(), v1.distanceTo(Vec3f::Null));
    ASSERT_FLOAT_EQ((v1 - v2).length(), v1.distanceTo(v2));
}