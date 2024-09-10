// TODO: clean up error handling, too much dupe code right now
bool PNG::_read_file(string const & file_name)
{
	// unfortunately, we need to break down to the C-code level here, since
	// libpng is written in C itself

	// we need to open the file in binary mode
	FILE * fp = fopen(file_name.c_str(), "rb");
	if (!fp)
	{
		epng_err("Failed to open " + file_name);
		return false;
	}

	// read in the header (max size of 8), use it to validate this as a PNG file
	png_byte header[8];
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
	{
		epng_err("File is not a valid PNG file");
		fclose(fp);
		_init();
		return false;
	}

	// set up libpng structs for reading info
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); if (!png_ptr)
	{
		epng_err("Failed to create read struct");
		fclose(fp);
		_init();
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		epng_err("Failed to create info struct");
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fclose(fp);
		_init();
		return false;
	}

	// set error handling to not abort the entire program
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Error initializing libpng io");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		_init();
		return false;
	}

	// initialize png reading
	png_init_io(png_ptr, fp);
	// let it know we've already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read in the basic image info
	png_read_info(png_ptr, info_ptr);

	// convert to 8 bits
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	if (bit_depth == 16)
		png_set_strip_16(png_ptr);

	// verify this is in RGBA format, and if not, convert it to RGBA
	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	if (color_type != PNG_COLOR_TYPE_RGBA && color_type != PNG_COLOR_TYPE_RGB)
	{
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
			if (bit_depth < 8)
				png_set_expand(png_ptr);
			png_set_gray_to_rgb(png_ptr);
		}
		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);
	}
	// convert tRNS to alpha channel
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	_width = png_get_image_width(png_ptr, info_ptr);
	_height = png_get_image_height(png_ptr, info_ptr);

	png_read_update_info(png_ptr, info_ptr);

	// begin reading in the image
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Error reading image with libpng");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		_init();
		return false;
	}


	int bpr = png_get_rowbytes(png_ptr, info_ptr); // number of bytes in a row
	int numchannels = png_get_channels(png_ptr, info_ptr);

	// initialie our image storage
	_pixels = new RGBAPixel[_height * _width];
	png_byte * row = new png_byte[bpr];
	for (int y = 0; y < _height; y++)
	{
		png_read_row(png_ptr, row, NULL);
		png_byte * pix = row;
		for (int x = 0; x < _width; x++)
		{
			RGBAPixel & pixel = _pixel(x,y);
			if (numchannels == 1 || numchannels == 2)
			{
				// monochrome
				unsigned char color = (unsigned char) *pix++;
				pixel.red = color;
				pixel.green = color;
				pixel.blue = color;
				if (numchannels == 2)
					pixel.alpha = (unsigned char) *pix++;
				else
					pixel.alpha = 255;
			} 
			else if (numchannels == 3 || numchannels == 4) 
			{
				pixel.red = (unsigned char) *pix++;
				pixel.green = (unsigned char) *pix++;
				pixel.blue = (unsigned char) *pix++;
				if (numchannels == 4)
					pixel.alpha = (unsigned char) *pix++;
				else
					pixel.alpha = 255;
			}
		}
	}
	// cleanup
	delete [] row;
	png_read_end(png_ptr, NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return true;
}