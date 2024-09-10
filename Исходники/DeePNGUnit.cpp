//---------------------------------------------------------------------------
void __fastcall TDeePNG::SaveToStream(Classes::TStream * Stream)
{
	// SaveToStream method
	// warning: this method would change the pixelformat to pf24bit
	// if the pixelformat is pfDevice, pf15bit, pf16bit, or pfCustom.


	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row_buffer = NULL;

	try
	{
		// create png_struct
		png_ptr = png_create_write_struct_2
			(PNG_LIBPNG_VER_STRING,
			(png_voidp)this, DeePNG_error, DeePNG_warning,
			(png_voidp)this, DeePNG_malloc, DeePNG_free);


		// create png_info
		info_ptr = png_create_info_struct(png_ptr);

		// set write function
		png_set_write_fn(png_ptr, (png_voidp)Stream,
			DeePNG_write_data, DeePNG_flush);


		// set IHDR
		if(PixelFormat == pfDevice || PixelFormat == pf15bit ||
			PixelFormat == pf16bit || PixelFormat == pfCustom)
			PixelFormat = pf24bit;

		bool grayscale = IsGrayscaleBitmap(this);
		int colordepth = GetBitmapColorDepth(this);

		int w = Width;
		int h = Height;

		int color_type;
		if(grayscale)
			color_type = PNG_COLOR_TYPE_GRAY;
		else if(colordepth <= 8)
			color_type = PNG_COLOR_TYPE_PALETTE;
		else if(colordepth == 32)
			color_type = PNG_COLOR_TYPE_RGB_ALPHA;
		else
			color_type = PNG_COLOR_TYPE_RGB;

		png_set_IHDR(png_ptr, info_ptr, w, h,
			colordepth < 8 ? colordepth : 8,
			color_type, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);

		// set oFFs
		if(ofs_set)
			png_set_oFFs(png_ptr, info_ptr, ofs_x, ofs_y, ofs_unit);

		// set palette
		if(color_type == PNG_COLOR_TYPE_PALETTE)
		{
			png_color *palette = (png_colorp)png_malloc(png_ptr, 256 * sizeof(png_color));
			PALETTEENTRY palentry[256];
			int num_palette = GetPaletteEntries(Palette, 0, (1<<colordepth), palentry);
			for(int i = 0; i < num_palette; i++)
			{
				palette[i].red = palentry[i].peRed;
				palette[i].green = palentry[i].peGreen;
				palette[i].blue = palentry[i].peBlue;
			}
			png_set_PLTE(png_ptr, info_ptr, palette, num_palette);
		}

		// write info
		png_write_info(png_ptr, info_ptr);

		// write vpAg private chunk
		if(vpag_set)
		{
			png_byte png_vpAg[5] = {118, 112,  65, 103, '\0'};
			unsigned char vpag_chunk_data[9];
		#define PNG_write_be32(p, a) (\
			((unsigned char *)(p))[0] = (unsigned char)(((a) >>24) & 0xff), \
			((unsigned char *)(p))[1] = (unsigned char)(((a) >>16) & 0xff), \
			((unsigned char *)(p))[2] = (unsigned char)(((a) >> 8) & 0xff), \
			((unsigned char *)(p))[3] = (unsigned char)(((a)     ) & 0xff)  )
			PNG_write_be32(vpag_chunk_data,     vpag_w);
			PNG_write_be32(vpag_chunk_data + 4, vpag_h);
			vpag_chunk_data[8] = (unsigned char)vpag_unit;
			png_write_chunk(png_ptr, png_vpAg, vpag_chunk_data, 9);
		}

/*
		// change RGB order
		if(color_type = PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		   png_set_bgr(png_ptr);
		// ???? why this does not work ?
*/
		// write image
		if(color_type == PNG_COLOR_TYPE_RGB)
		{
			row_buffer = (png_bytep)png_malloc(png_ptr, 3 * w + 6);
			try
			{
				png_bytep row_pointer = row_buffer;

				for(int i = 0; i < h; i++)
				{
					png_bytep in = (png_bytep)ScanLine[i];
					png_bytep out = row_buffer;
					for(int x = 0; x < w; x++)
					{
						out[2] = in[0];
						out[1] = in[1];
						out[0] = in[2];
						out += 3;
						in += 3;
					}
					png_write_row(png_ptr, row_pointer);
				}
			}
			catch(...)
			{
				png_free(png_ptr, row_buffer);
				throw;
			}
			png_free(png_ptr, row_buffer);
		}
		else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		{
			row_buffer = (png_bytep)png_malloc(png_ptr, 4 * w + 6);
			try
			{
				png_bytep row_pointer = row_buffer;

				for(int i = 0; i < h; i++)
				{
					png_bytep in = (png_bytep)ScanLine[i];
					png_bytep out = row_buffer;
					for(int x = 0; x < w; x++)
					{
						out[2] = in[0];
						out[1] = in[1];
						out[0] = in[2];
						out[3] = in[3];
						out += 4;
						in += 4;
					}
					png_write_row(png_ptr, row_pointer);
				}
			}
			catch(...)
			{
				png_free(png_ptr, row_buffer);
				throw;
			}
			png_free(png_ptr, row_buffer);
		}
		else
		{
			for(int i = 0; i < h; i++)
			{
				png_bytep row_pointer = (png_bytep)ScanLine[i];
				png_write_row(png_ptr, row_pointer);
			}
		}


		// finish writing
		png_write_end(png_ptr, info_ptr);

	}
	catch(...)
	{
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw;
	}

	png_destroy_write_struct(&png_ptr, &info_ptr);
}