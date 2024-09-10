TEST(BoundingSphere, Intersects_BoundingBox)
{
    BoundingSphere sphere;
    sphere.Center = Vector3::Zero;
    sphere.Radius = 42.0f;

    auto min = Vector3::Normalize({-1.f, -1.f, -1.f}) * 42.0f;
    auto max = Vector3::Normalize({1.f, 1.f, 1.f}) * 42.0f;
    auto unit = Vector3::Normalize({1.f, 1.f, 1.f}) * 42.0f;

    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero, max}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero - unit * Vector3::UnitX, max - unit * Vector3::UnitX}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero - unit * Vector3::UnitY, max - unit * Vector3::UnitY}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero - unit * Vector3::UnitZ, max - unit * Vector3::UnitZ}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min, Vector3::Zero}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min + unit * Vector3::UnitX, Vector3::Zero + unit * Vector3::UnitX}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min + unit * Vector3::UnitY, Vector3::Zero + unit * Vector3::UnitY}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min + unit * Vector3::UnitZ, Vector3::Zero + unit * Vector3::UnitZ}));

    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero, max * 1.01f}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero - unit * Vector3::UnitX, max * 1.01f - unit * Vector3::UnitX}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero - unit * Vector3::UnitY, max * 1.01f - unit * Vector3::UnitY}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{Vector3::Zero - unit * Vector3::UnitZ, max * 1.01f - unit * Vector3::UnitZ}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min * 1.01f, Vector3::Zero}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min * 1.01f + unit * Vector3::UnitX, Vector3::Zero + unit * Vector3::UnitX}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min * 1.01f + unit * Vector3::UnitY, Vector3::Zero + unit * Vector3::UnitY}));
    EXPECT_TRUE(sphere.Intersects(BoundingBox{min * 1.01f + unit * Vector3::UnitZ, Vector3::Zero + unit * Vector3::UnitZ}));

    EXPECT_FALSE(sphere.Intersects(BoundingBox{max * 1.01f, max * 1.01f + unit}));
}