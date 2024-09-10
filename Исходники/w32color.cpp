bool MCScreenDC::transformimagecolors(MCColorTransformRef transform, MCImageBitmap *p_image)
{
	MCWindowsColorTransform *t_transform;
	t_transform = (MCWindowsColorTransform *)transform;

	bool t_success;
	t_success = true;

	if (t_success)
	{
		// If the src color space is of CMYK type, then we assume the input data
		// is in that colorspace.
		BMFORMAT t_input_format;
		if (t_transform -> is_cmyk)
			t_input_format = BM_KYMCQUADS;
		else
			t_input_format = BM_xRGBQUADS;

		if (t_transform != nil &&
			!TranslateBitmapBits(t_transform -> transform, p_image -> data, t_input_format, p_image -> width, p_image -> height, p_image -> stride, p_image -> data, BM_xRGBQUADS, p_image -> stride, nil, INDEX_DONT_CARE))
			t_success = false;
	}

	return t_success;
}