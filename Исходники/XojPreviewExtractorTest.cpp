	void testLoadGzipped2()
	{
		XojPreviewExtractor extractor;
		PreviewExtractResult result = extractor.readFile(GET_TESTFILE("preview-test2.xoj"));

		CPPUNIT_ASSERT_EQUAL(PREVIEW_RESULT_IMAGE_READ, result);

		gsize dataLen = 0;
		extractor.getData(dataLen);
		CPPUNIT_ASSERT_EQUAL((std::string::size_type) 2856, dataLen);
	}