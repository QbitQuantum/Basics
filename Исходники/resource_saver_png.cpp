Error ResourceSaverPNG::save_image(const String &p_path, Image &p_img) {

	if (p_img.get_format() > Image::FORMAT_INDEXED_ALPHA)
		p_img.decompress();

	ERR_FAIL_COND_V(p_img.get_format() > Image::FORMAT_INDEXED_ALPHA, ERR_INVALID_PARAMETER);

	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep * row_pointers;


	/* initialize stuff */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	ERR_FAIL_COND_V(!png_ptr,ERR_CANT_CREATE);

	info_ptr = png_create_info_struct(png_ptr);

	ERR_FAIL_COND_V(!info_ptr,ERR_CANT_CREATE);

	if (setjmp(png_jmpbuf(png_ptr))) {
		ERR_FAIL_V(ERR_CANT_OPEN);
	}
	//change this
	Error err;
	FileAccess* f = FileAccess::open(p_path,FileAccess::WRITE,&err);
	if (err) {
		ERR_FAIL_V(err);
	}

	png_set_write_fn(png_ptr,f,_write_png_data,NULL);

	/* write header */
	if (setjmp(png_jmpbuf(png_ptr))) {
		ERR_FAIL_V(ERR_CANT_OPEN);
	}

	int pngf=0;
	int pngb=8;
	int cs=0;


	switch(p_img.get_format()) {

		case Image::FORMAT_GRAYSCALE: {

			pngf=PNG_COLOR_TYPE_GRAY;
			cs=1;
		} break;
		case Image::FORMAT_GRAYSCALE_ALPHA: {

			pngf=PNG_COLOR_TYPE_GRAY_ALPHA;
			cs=2;
		} break;
		case Image::FORMAT_RGB: {

			pngf=PNG_COLOR_TYPE_RGB;
			cs=3;
		} break;
		case Image::FORMAT_RGBA: {

			pngf=PNG_COLOR_TYPE_RGB_ALPHA;
			cs=4;
		} break;
		default: {

			if (p_img.detect_alpha()) {

				p_img.convert(Image::FORMAT_RGBA);
				pngf=PNG_COLOR_TYPE_RGB_ALPHA;
				cs=4;
			} else {

				p_img.convert(Image::FORMAT_RGB);
				pngf=PNG_COLOR_TYPE_RGB;
				cs=3;
			}

		}
	}

	int w = p_img.get_width();
	int h = p_img.get_height();
	png_set_IHDR(png_ptr, info_ptr, w,h,
		     8, pngf, PNG_INTERLACE_NONE,
		     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);


	/* write bytes */
	if (setjmp(png_jmpbuf(png_ptr))) {
		memdelete(f);
		ERR_FAIL_V(ERR_CANT_OPEN);
	}


	DVector<uint8_t>::Read r = p_img.get_data().read();

	row_pointers = (png_bytep*)memalloc(sizeof(png_bytep)*h);
	for(int i=0;i<h;i++) {

		row_pointers[i]=(png_bytep)&r[i*w*cs];
	}
	png_write_image(png_ptr, row_pointers);

	memfree(row_pointers);

	/* end write */
	if (setjmp(png_jmpbuf(png_ptr))) {

		memdelete(f);
		ERR_FAIL_V(ERR_CANT_OPEN);
	}

	png_write_end(png_ptr, NULL);
	memdelete(f);

	/* cleanup heap allocation */

	return OK;
}