void
BitmapImage::CreateLoader (unsigned char *buffer)
{
	if (!(moonlight_flags & RUNTIME_INIT_ALL_IMAGE_FORMATS)) {
		// 89 50 4E 47 == png magic
		if (buffer[0] == 0x89)
			loader = runtime_get_windowing_system()->CreatePixbufLoader ("png");
		// ff d8 ff e0 == jfif magic
		else if (buffer[0] == 0xff)
			loader = runtime_get_windowing_system()->CreatePixbufLoader ("jpeg");

		else {
			Abort ();
			moon_error = new MoonError (MoonError::EXCEPTION, 4001, "unsupported image type");
		}
	} else {
		loader = runtime_get_windowing_system()->CreatePixbufLoader (NULL);
	}
}