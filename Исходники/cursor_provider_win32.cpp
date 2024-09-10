	DataBuffer CursorProvider_Win32::create_ico_file(const PixelBuffer &image)
	{
		return create_ico_helper(image, Rectf(image.get_size()), 1, Point(0, 0));
	}