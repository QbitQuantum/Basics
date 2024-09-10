void VisualExplodingImage::ExplosionUnit::setColor(uint32 color, const Graphics::PixelFormat &format) {
	_mainColor = color;

	byte a, r, g, b;
	format.colorToARGB(color, a, r, g, b);
	r >>= 1;
	g >>= 1;
	b >>= 1;

	_darkColor = format.ARGBToColor(a, r, g, b);
}