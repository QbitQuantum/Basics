TEST(FileHeaderTest, WindowsBitmapHeader)
{
	std::ifstream bitmapStream("basic.bmp", std::ios::binary);
	CHECK(bitmapStream.is_open());

	WindowsBitmapHeader bitmapHeader;
	bitmapHeader.readFileHeader(bitmapStream);

	// The "basic.bmp" image is 100x100 = 10000 pixels.
	// Each pixel is 3 bytes (1 red, 1 green, 1 blue),
	// so the bitmap image pixel data is 30000 bytes.
	// The header data is 54 bytes, so we expect 30054
	// total file size.

	CHECK_EQUAL(30054, bitmapHeader.getFileSize());

	// We could also check the file size this way:

	bitmapStream.seekg(0, std::ifstream::end);
	CHECK_EQUAL(int(bitmapStream.tellg()), bitmapHeader.getFileSize());
}