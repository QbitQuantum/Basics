static bool load_from_pixels(Image &img, const void *pixels, size_t width, size_t height, size_t channels, bool rendian=false) {
	img.create(width, height);
	const unsigned char *p0 = (const unsigned char*)pixels;
	for(size_t y=0; y < height; y++) {
		const unsigned char *p = p0+y*width*channels;
		for(size_t x=0; x < width; x++) {
			img.setPixel(x,y,(rendian?Color(p[2],p[1],p[0],p[3]):Color(p[0],p[1],p[2],p[3])));
			p += channels;
		}
	}
	return true;
}