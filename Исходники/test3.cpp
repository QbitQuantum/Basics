	void testInversion()
	{
		float data1[] =
		{
			1,2,3,4,
			2,3,4,1,
			3,4,1,2,
			4,1,2,3
		};

		float data2[] =
		{
			-9,  1,  1, 11,
			 1,  1, 11, -9,
			 1, 11, -9,  1,
			11, -9,  1,  1
		};

		mi1 = Matrix4f(data1);
		mi2 = mi1.inverse();
		Matrix4f imr(data2);
		imr = imr * 1/40.0f;

		/*
		std::cout << "mi1 = \n" << mi1 << std::endl;
		std::cout << "mi2 = \n" << mi2 << std::endl;
		std::cout << "imr = \n" << imr << std::endl;
		*/
		CPPUNIT_ASSERT(mi2 == imr);

	}