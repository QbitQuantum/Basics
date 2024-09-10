void ImageFilter_PNG::save (const Drawable &surface, FileObject &file, const AssocArray &param)
{
#ifdef HAVE_PNG
	Color farbe;
	int pitch,colortype;
	//int r,g,b,a;
	int width,height;
	png_byte *buffer;
	png_color	pc[256];
	//RGBA	rgb;

	if (surface.isEmpty()) throw EmptyImageException();

	file.seek(0);
	width=surface.width();
	height=surface.height();

	pitch=colortype=0;
	int png_color_type=PNG_COLOR_TYPE_GRAY;
	int compression_level=Z_BEST_COMPRESSION;
	RGBFormat srgb=surface.rgbformat();
	if (srgb==RGBFormat::A8R8G8B8) png_color_type=PNG_COLOR_TYPE_RGB_ALPHA;

	if (param.exists("colortype")) png_color_type=param.getString("colortype").toInt();
	if (!png_color_type) png_color_type=PNG_COLOR_TYPE_RGB;

	switch (png_color_type) {
		case PNG_COLOR_TYPE_GRAY:
			colortype=PNG_COLOR_TYPE_GRAY;
			pitch=width*1;
			break;
		case PNG_COLOR_TYPE_PALETTE:
			colortype=PNG_COLOR_TYPE_PALETTE;
			pitch=width*1;
			break;
		case PNG_COLOR_TYPE_RGB:
			colortype=PNG_COLOR_TYPE_RGB;
			pitch=width*3;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			colortype=PNG_COLOR_TYPE_RGB_ALPHA;
			pitch=width*4;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			colortype=PNG_COLOR_TYPE_GRAY_ALPHA;
			pitch=width*2;
			break;
		default:
			colortype=PNG_COLOR_TYPE_RGB;
			pitch=width*3;
			break;
	};


	png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);
	if (!png_ptr) throw OperationFailedException("ImageFilter_PNG::save");
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
		throw OperationFailedException("ImageFilter_PNG::save");
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr,&info_ptr);
		throw OperationFailedException("ImageFilter_PNG::save");
	}

	//png_set_read_fn(png_ptr,(voidp) file, (png_rw_ptr) user_read_data);
	png_set_write_fn(png_ptr, &file, (png_rw_ptr) user_write_data, (png_flush_ptr) user_flush_data);

	// Compression-Level setzen

	png_set_compression_level (png_ptr, compression_level);




	png_set_IHDR(png_ptr, info_ptr, width,height,8,colortype,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);




	buffer=(png_byte*)png_malloc(png_ptr,pitch);
	if (!buffer) {
		png_destroy_write_struct(&png_ptr,&info_ptr);
		throw OutOfMemoryException();
	}
	if (buffer!=NULL) {
		// png_write_row(png_ptr, row_pointer);
		int bpp;
		switch (colortype) {
			case PNG_COLOR_TYPE_PALETTE:
				bpp=1;
				if (surface.rgbformat()==RGBFormat::Palette) {	// Surface verwendet Palette
					for (int i=0;i<256;i++) {
						// TODO:
						//surface->GetColor(i,&rgb);
						//pc[i].red=rgb.red;
						//pc[i].green=rgb.green;
						//pc[i].blue=rgb.blue;
					}
					png_set_PLTE(png_ptr,info_ptr, &pc[0], 256);
					png_write_info(png_ptr, info_ptr);
					//png_write_PLTE (png_ptr, &pc[0],256);

					for (int y=0;y<height;y++) {
						for (int x=0;x<width;x++) {
							farbe=surface.getPixel(x,y);
							buffer[x]=(ppluint8)(farbe.color()&0xff);
						}
						png_write_row(png_ptr, buffer);
					}
				} else {								// Surface verwendet keine Palette -> Konvertierung
					/* TODO:
					RGBA *pal=Get8BitTrueColorPalette ();
					for (int i=0;i<256;i++) {
						pc[i].red=pal[i].c.red;
						pc[i].green=pal[i].c.green;
						pc[i].blue=pal[i].c.blue;
						DLOG ("Farbe %i: RGB=%u, %u, %u",i,pc[i].red,pc[i].green,pc[i].blue);
					}
					png_set_PLTE(png_ptr,info_ptr, &pc[0], 256);
					png_write_info(png_ptr, info_ptr);
					//png_write_PLTE (png_ptr, &pc[0],256);

					for (y=area->top;y<area->bottom;y++) {
						DLOGLEVEL(2) ("png_write_row Zeile %u",y);
						for (x=0;x<width;x++) {
							farbe=surface->Surface2RGB(surface->GetPixel(area->left+x,y));
							r=(farbe&255)*7/255;
							g=((farbe>>8)&255)*7/255;
							b=((farbe>>16)&255)*3/255;
							buffer[x]=(ppldb)(r+(g<<3)+(b<<6));
						}
						png_write_row(png_ptr, buffer);
					}
					 */

				}
				break;
			case PNG_COLOR_TYPE_RGB:
				bpp=3;
				png_write_info(png_ptr, info_ptr);
				for (int y=0;y<height;y++) {
					for (int x=0;x<width;x++) {
						//farbe=surface->GetPixel(area->left+x,y);
						farbe=surface.getPixel(x,y);
						buffer[x*bpp+0]=(ppluint8)farbe.red();
						buffer[x*bpp+1]=(ppluint8)farbe.green();
						buffer[x*bpp+2]=(ppluint8)farbe.blue();
					}
					png_write_row(png_ptr, buffer);
				}
				break;
			case PNG_COLOR_TYPE_RGB_ALPHA:
				bpp=4;
				png_write_info(png_ptr, info_ptr);
				for (int y=0;y<height;y++) {
					for (int x=0;x<width;x++) {
						farbe=surface.getPixel(x,y);
						buffer[x*bpp+0]=(ppluint8)farbe.red();
						buffer[x*bpp+1]=(ppluint8)farbe.green();
						buffer[x*bpp+2]=(ppluint8)farbe.blue();
						buffer[x*bpp+3]=(ppluint8)farbe.alpha();
					}
					png_write_row(png_ptr, buffer);
				}
				break;
			case PNG_COLOR_TYPE_GRAY:
				bpp=1;
				png_write_info(png_ptr, info_ptr);
				for (int y=0;y<height;y++) {
					for (int x=0;x<width;x++) {
						farbe=surface.getPixel(x,y);
						buffer[x*bpp]=(ppluint8)farbe.brightness();
					}
					png_write_row(png_ptr, buffer);
				}

				break;
			case PNG_COLOR_TYPE_GRAY_ALPHA:
				bpp=2;
				png_write_info(png_ptr, info_ptr);
				for (int y=0;y<height;y++) {
					for (int x=0;x<width;x++) {
						farbe=surface.getPixel(x,y);
						buffer[x*bpp]=(ppluint8)farbe.brightness();
						buffer[x*bpp+1]=(ppluint8)farbe.alpha();
					}
					png_write_row(png_ptr, buffer);
				}
				break;
		}
		png_free(png_ptr,buffer);
	}

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr,&info_ptr);
#else
	throw UnsupportedFeatureException("ImageFilter_PNG");
#endif

}