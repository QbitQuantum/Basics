int ExtractBits(PNG_CONST TCHAR *inname, PNG_CONST TCHAR *outname)
{
	static HANDLE fpin;
	static HANDLE fpout;  /* "static" prevents setjmp corruption */
	png_structp read_ptr;
	png_infop read_info_ptr, end_info_ptr;
	png_structp write_ptr = NULL;
	png_infop write_info_ptr = NULL;
	png_infop write_end_info_ptr = NULL;
	png_bytep row_buf;
	png_uint_32 y;
	png_uint_32 width, height;
	int num_pass, pass;
	int bit_depth, color_type;
	char inbuf[256], outbuf[256];
	row_buf = NULL;

	if ((fpin = CreateFile(inname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		fprintf(STDERR, "Could not find input file %s\n", inname);
		return (1);
	}

	if ((fpout = CreateFile(outname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		fprintf(STDERR, "Could not open output file %s\n", outname);
		FCLOSE(fpin);
		return (1);
	}

	png_debug(0, "Allocating read and write structures");
	read_ptr =
	    png_create_read_struct(PNG_LIBPNG_VER_STRING, png_voidp_NULL,
	                           png_error_ptr_NULL, png_error_ptr_NULL);
	png_set_error_fn(read_ptr, (png_voidp)inname, pngtest_error,
	                 pngtest_warning);
	png_debug(0, "Allocating read_info, write_info and end_info structures");
	read_info_ptr = png_create_info_struct(read_ptr);
	end_info_ptr = png_create_info_struct(read_ptr);
	png_debug(0, "Setting jmpbuf for read struct");

	if (setjmp(png_jmpbuf(read_ptr)))
	{
		fprintf(STDERR, "%s -> %s: libpng read error\n", inname, outname);
		png_free(read_ptr, row_buf);
		row_buf = NULL;
		png_destroy_read_struct(&read_ptr, &read_info_ptr, &end_info_ptr);
		FCLOSE(fpin);
		FCLOSE(fpout);
		return (1);
	}

	png_debug(0, "Initializing input and output streams");
	png_set_read_fn(read_ptr, (png_voidp)fpin, pngtest_read_data);

	if (status_dots_requested == 1)
	{
		png_set_read_status_fn(read_ptr, read_row_callback);
	}
	else
	{
		png_set_read_status_fn(read_ptr, png_read_status_ptr_NULL);
	}

	png_debug(0, "Reading info struct");
	png_read_info(read_ptr, read_info_ptr);
	png_debug(0, "Transferring info struct");
	{
		int interlace_type, compression_type, filter_type;

		if (png_get_IHDR(read_ptr, read_info_ptr, &width, &height, &bit_depth,
		                &color_type, &interlace_type, &compression_type, &filter_type))
		{
			png_set_IHDR(write_ptr, write_info_ptr, width, height, bit_depth,
			             color_type, PNG_INTERLACE_NONE, compression_type, filter_type);
		}
	}
	{
		int intent;

		if (png_get_sRGB(read_ptr, read_info_ptr, &intent))
			png_set_sRGB(write_ptr, write_info_ptr, intent);
	}
	{
		png_colorp palette;
		int num_palette;

		if (png_get_PLTE(read_ptr, read_info_ptr, &palette, &num_palette))
			png_set_PLTE(write_ptr, write_info_ptr, palette, num_palette);
	}
	{
		png_color_8p sig_bit;

		if (png_get_sBIT(read_ptr, read_info_ptr, &sig_bit))
			png_set_sBIT(write_ptr, write_info_ptr, sig_bit);
	}
	{
		png_bytep trans;
		int num_trans;
		png_color_16p trans_values;

		if (png_get_tRNS(read_ptr, read_info_ptr, &trans, &num_trans,
		                &trans_values))
		{
			int sample_max = (1 << read_info_ptr->bit_depth);

			/* libpng doesn't reject a tRNS chunk with out-of-range samples */
			if (!((read_info_ptr->color_type == PNG_COLOR_TYPE_GRAY &&
			        (int)trans_values->gray > sample_max) ||
			        (read_info_ptr->color_type == PNG_COLOR_TYPE_RGB &&
			         ((int)trans_values->red > sample_max ||
			          (int)trans_values->green > sample_max ||
			          (int)trans_values->blue > sample_max))))
				png_set_tRNS(write_ptr, write_info_ptr, trans, num_trans,
				             trans_values);
		}
	}
	png_debug(0, "Writing row data");
	num_pass = png_set_interlace_handling(read_ptr);

	for(pass = 0; pass < num_pass; pass++)
	{
		png_debug1(0, "Writing row data for pass %d", pass);

		for(y = 0; y < height; y++)
		{
			png_debug2(0, "Allocating row buffer (pass %d, y = %ld)...", pass, y);
			row_buf = (png_bytep)png_malloc(read_ptr,
			                                png_get_rowbytes(read_ptr, read_info_ptr));
			png_debug2(0, "0x%08lx (%ld bytes)", (unsigned long)row_buf,
			           png_get_rowbytes(read_ptr, read_info_ptr));
			png_read_rows(read_ptr, (png_bytepp)&row_buf, png_bytepp_NULL, 1);
			png_debug2(0, "Freeing row buffer (pass %d, y = %ld)", pass, y);
			png_free(read_ptr, row_buf);
			row_buf = NULL;
		}
	}

	png_debug(0, "Reading and writing end_info data");
	png_read_end(read_ptr, end_info_ptr);
	{
		png_uint_32 iwidth, iheight;
		iwidth = png_get_image_width(write_ptr, write_info_ptr);
		iheight = png_get_image_height(write_ptr, write_info_ptr);
		fprintf(STDERR, "\n Image width = %lu, height = %lu\n",
		        (unsigned long)iwidth, (unsigned long)iheight);
	}
	png_debug(0, "Destroying data structs");
	png_debug(1, "destroying read_ptr, read_info_ptr, end_info_ptr");
	png_destroy_read_struct(&read_ptr, &read_info_ptr, &end_info_ptr);
	png_debug(0, "Destruction complete.");
	FCLOSE(fpin);
	FCLOSE(fpout);
	png_debug(0, "Opening files for comparison");

	if ((fpin = CreateFile(inname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		fprintf(STDERR, "Could not find file %s\n", inname);
		return (1);
	}

	if ((fpout = CreateFile(outname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		fprintf(STDERR, "Could not find file %s\n", outname);
		FCLOSE(fpin);
		return (1);
	}

	for(;;)
	{
		DWORD num_in, num_out;
		READFILE(fpin, inbuf, 1, num_in);
		READFILE(fpout, outbuf, 1, num_out);

		if (num_in != num_out)
		{
			fprintf(STDERR, "\nFiles %s and %s are of a different size\n",
			        inname, outname);

			if (wrote_question == 0)
			{
				fprintf(STDERR,
				        "   Was %s written with the same maximum IDAT chunk size (%d bytes),",
				        inname, PNG_ZBUF_SIZE);
				fprintf(STDERR,
				        "\n   filtering heuristic (libpng default), compression");
				fprintf(STDERR,
				        " level (zlib default),\n   and zlib version (%s)?\n\n",
				        ZLIB_VERSION);
				wrote_question = 1;
			}

			FCLOSE(fpin);
			FCLOSE(fpout);
			return (0);
		}

		if (!num_in)
			break;

		if (png_memcmp(inbuf, outbuf, num_in))
		{
			fprintf(STDERR, "\nFiles %s and %s are different\n", inname, outname);

			if (wrote_question == 0)
			{
				fprintf(STDERR,
				        "   Was %s written with the same maximum IDAT chunk size (%d bytes),",
				        inname, PNG_ZBUF_SIZE);
				fprintf(STDERR,
				        "\n   filtering heuristic (libpng default), compression");
				fprintf(STDERR,
				        " level (zlib default),\n   and zlib version (%s)?\n\n",
				        ZLIB_VERSION);
				wrote_question = 1;
			}

			FCLOSE(fpin);
			FCLOSE(fpout);
			return (0);
		}
	}

	FCLOSE(fpin);
	FCLOSE(fpout);
	return (0);
}