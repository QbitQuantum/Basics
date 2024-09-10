	void SamplePointTest()
	{
		DIBitmap24 bitmap;
		bitmap.setWidth(640);
		bitmap.setHeight(480);

		bool result = bitmap.createDIBSection();
		if (result == false)
		{
			std::cout << "\nerror code is " << GetLastError() << std::endl;
		}
		CPPUNIT_ASSERT(result);
			

		for(size_t y = 0; y < 256; ++y)
			for(size_t x = 0; x < 256; ++x)
				bitmap.getPixel(x, y)->setColor(Color(x, x, x));

		const TestDIB4 scanner4(bitmap);
		for(size_t y = 0; y < 256; ++y)
		{
			for(size_t x = 0; x < 256; ++x)
			{
				CPPUNIT_ASSERT(
					scanner4.getPixel(x, y)->getColor() ==
					bitmap.getPixel(x, y)->getColor());
			}
		}

		const TestDIB2 scanner2(bitmap);
		for(size_t y = 0; y < 256; ++y)
		{
			for(size_t x = 0; x < 128; ++x)
			{
				CPPUNIT_ASSERT(
					scanner2.getPixel(x, y)->getColor() ==
					bitmap.getPixel(x << 1, y)->getColor());
			}
		}


		TestDIB1 scanner1(bitmap);
		for(size_t y = 0; y < 128; ++y)
		{
			for(size_t x = 0; x < 128; ++x)
			{
				CPPUNIT_ASSERT(
					scanner1.getPixel(x, y)->getColor() ==
					bitmap.getPixel(x << 1, y << 1)->getColor());
			}
		}
	}