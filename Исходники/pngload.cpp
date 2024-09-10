ImgColor* 
load_png(const char* filename, int *width, int *height, int *channels )
{
    png_byte header[8];	// 8 is the maximum size that can be checked
    int x,y;

    // open file and test for it being a png
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        dbg(DBG_ERROR,"[read_png_file] File %s could not "
            "be opened for reading", filename);
        return NULL;
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        dbg(DBG_ERROR,"[read_png_file] File %s is not "
            "recognized as a PNG file", filename);
        return NULL;
    }
    
    /* initialize stuff */
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if (!png_ptr) {
        dbg(DBG_ERROR,"[read_png_file] png_create_read_struct failed");
        return NULL;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        dbg(DBG_ERROR,"[read_png_file] png_create_info_struct failed");
        return NULL;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        dbg(DBG_ERROR,"[read_png_file] Error during init_io");
        return NULL;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    
    png_read_info(png_ptr, info_ptr);
    
    *width = (int)info_ptr->width;
    *height = (int)info_ptr->height;
    png_byte color_type = info_ptr->color_type;
    png_byte bit_depth = info_ptr->bit_depth;
    
    dbg(DBG_INFO, "[read_png_file] width: %d  height: %d  color type: %d  bit_depth: %d\n", *width, *height,\
        color_type, bit_depth);

    //int number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
    
    
    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        dbg(DBG_ERROR,"[read_png_file] Error during read_image");
    
    png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * *height);
    for (y=0; y<*height; y++)
        row_pointers[y] = (png_byte*) malloc(info_ptr->rowbytes);
    
    png_read_image(png_ptr, row_pointers);
    
    // copy to image color structure
    ImgColor *img = new ImgColor( *width, *height );
    
    if ( color_type == 2 ) {
        // RGB color type
        for (y=0;y<*height;y++) {
            for (x=0;x<*width;x++) {
                img->SetPixel( x, y, row_pointers[y][3*x+2],row_pointers[y][3*x+1], row_pointers[y][3*x]);
            }
        }
    } else if ( color_type == 1 ) {
        // grayscale
        for (y=0;y<*height;y++) {
            for (x=0;x<*width;x++) {
                img->SetPixel( x, y, row_pointers[y][x],row_pointers[y][x], row_pointers[y][x]);
            }
        }
    }

    fclose(fp);
    
    // free memory
    for (y=0; y<*height; y++)
        free ( row_pointers[y] );
    free( row_pointers );

    return img;
    
}