GTEST_TEST(RageRect, float_center)
{
	using namespace Rage;
	
	RectF test;
	
	RectF bigger{ -1, -1, 1, 1 };
	
	EXPECT_EQ(test.GetCenterX(), bigger.GetCenterX());
	EXPECT_EQ(test.GetCenterY(), bigger.GetCenterY());
}