TEST(vec2d, norm)
{
	Vector2D testingVector = Vector2D();

	testingVector.x = 1;
	testingVector.y = 0;
	testingVector.Magnitude();
	testingVector.Normalize();
	EXPECT_FLOAT_EQ(1.f, testingVector.x);
	EXPECT_FLOAT_EQ(0.f, testingVector.y);
}