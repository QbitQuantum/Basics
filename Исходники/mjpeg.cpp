const Graphics::Surface *JPEGDecoder::decodeImage(Common::SeekableReadStream* stream) {
	if (!_jpeg->read(stream)) {
		warning("Failed to decode JPEG frame");
		return 0;
	}

	if (!_surface) {
		_surface = new Graphics::Surface();
		_surface->create(_jpeg->getWidth(), _jpeg->getHeight(), _pixelFormat.bytesPerPixel);
	}

	Graphics::Surface *frame = _jpeg->getSurface(_pixelFormat);
	assert(frame);

	_surface->copyFrom(*frame);

	frame->free();
	delete frame;

	return _surface;
}