RefPtr <Image>
TrueTypeFont::getCharImage(uint32_t c)
{
	// load glyph for the given character
	if(FT_Load_Char(face, c, FT_LOAD_RENDER))
		throw Exception("TrueTypeFont::getCharImage(): FT_Load_Char failed");

	uint8_t *glyphData = face->glyph->bitmap.buffer;
	unsigned int width = face->glyph->bitmap.width;
	unsigned int height = face->glyph->bitmap.rows;

	// create image
	RefPtr <Image> img = Image::create(width, height, 1);
	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {
			Color pixel;

			pixel.r = glyphData[width * y + x];
			pixel.g = pixel.b = pixel.a = pixel.r;

			img->setPixel(x, y, pixel);
		}
	}

	return img;
}