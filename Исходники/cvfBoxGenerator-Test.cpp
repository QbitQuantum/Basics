//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
TEST(BoxGeneratorTest, GenerateSimple)
{
    // From min/max
    {
        BoxGenerator gen;
        gen.setMinMax(Vec3d(10, 20, 30), Vec3d(20, 40, 60));

        BuilderTrisQuads builder;
        gen.generate(&builder);
        BoundingBox bb = builder.vertexBoundingBox();
        EXPECT_DOUBLE_EQ(10, bb.min().x());
        EXPECT_DOUBLE_EQ(20, bb.min().y());
        EXPECT_DOUBLE_EQ(30, bb.min().z());
        EXPECT_DOUBLE_EQ(20, bb.max().x());
        EXPECT_DOUBLE_EQ(40, bb.max().y());
        EXPECT_DOUBLE_EQ(60, bb.max().z());

        EXPECT_EQ(0, builder.triCount());
        EXPECT_EQ(6, builder.quadCount());
    }

    // From origin and extent
    {
        BoxGenerator gen;
        gen.setOriginAndExtent(Vec3d(10, 20, 30), Vec3d(100, 200, 300));

        BuilderTrisQuads builder;
        gen.generate(&builder);
        BoundingBox bb = builder.vertexBoundingBox();
        EXPECT_DOUBLE_EQ(10,  bb.min().x());
        EXPECT_DOUBLE_EQ(20,  bb.min().y());
        EXPECT_DOUBLE_EQ(30,  bb.min().z());
        EXPECT_DOUBLE_EQ(110, bb.max().x());
        EXPECT_DOUBLE_EQ(220, bb.max().y());
        EXPECT_DOUBLE_EQ(330, bb.max().z());
    }

    // From center and extent
    {
        BoxGenerator gen;
        gen.setCenterAndExtent(Vec3d(100, 200, 300), Vec3d(10, 20, 30));

        BuilderTrisQuads builder;
        gen.generate(&builder);
        BoundingBox bb = builder.vertexBoundingBox();
        EXPECT_DOUBLE_EQ(95,  bb.min().x());
        EXPECT_DOUBLE_EQ(190, bb.min().y());
        EXPECT_DOUBLE_EQ(285,  bb.min().z());
        EXPECT_DOUBLE_EQ(105, bb.max().x());
        EXPECT_DOUBLE_EQ(210, bb.max().y());
        EXPECT_DOUBLE_EQ(315, bb.max().z());
    }
}