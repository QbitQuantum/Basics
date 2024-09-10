static void
pngtest_write_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	png_uint_32 check;
	WRITEFILE((png_FILE_p)png_ptr->io_ptr,  data, length, check);
	if (check != length)
		png_error(png_ptr, "Write Error");
}