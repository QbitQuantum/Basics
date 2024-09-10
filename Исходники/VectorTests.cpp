template<class Vec> void testCross()
{
	Vec vec;
	for (unsigned int i = 0; i < vec.getDimension(); i++)
		vec[i] = numbers[i];
	Vec vec2;
	for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
		vec2[i] = numbers[i];

	auto temp = vec.cross(vec2);
	ASSERT_EQ(temp.getDimension(), vec.getDimension());
	for (unsigned int i = 0; i < temp.getDimension(); i++)
	{
		unsigned int i1 = i + 1;
		unsigned int i2 = i + 2;
		if (i2 >= temp.getDimension())
			i2 -= temp.getDimension();
		if (i1 >= temp.getDimension())
			i1 -= temp.getDimension();
		ASSERT(dbgl::isSimilar(temp[i], vec[i1] * vec2[i2] - vec[i2] * vec2[i1]));
	}
}