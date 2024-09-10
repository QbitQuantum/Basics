bool SavePartSprite::writeSprite(Surface &sprite) const {
	// The sprite's dimensions have to fit
	if (((uint32)sprite.getWidth()) != _width)
		return false;
	if (((uint32)sprite.getHeight()) != _height)
		return false;

	if (_trueColor) {
		if (sprite.getBPP() <= 1)
			return false;

		Graphics::PixelFormat pixelFormat = g_system->getScreenFormat();

		const byte *data = _dataSprite;
		Pixel pixel = sprite.get();
		for (uint32 i = 0; i < (_width * _height); i++, ++pixel, data += 3)
			pixel.set(pixelFormat.RGBToColor(data[0], data[1], data[2]));

	} else {
		if (sprite.getBPP() != 1)
			return false;

		memcpy(sprite.getData(), _dataSprite, _spriteSize);
	}

	return true;
}