bool SkPNGImageDecoder::onDecode(SkStream* sk_stream, SkBitmap* decodedBitmap,
                                 SkBitmap::Config prefConfig, Mode mode) {
//    SkAutoTrace    apr("SkPNGImageDecoder::onDecode");

    /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also supply the
    * the compiler header file version, so that we know if the application
    * was compiled with a compatible version of the library.  */
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
        NULL, sk_error_fn, NULL);
    //   png_voidp user_error_ptr, user_error_fn, user_warning_fn);
    if (png_ptr == NULL) {
        return false;
    }

    /* Allocate/initialize the memory for image information. */
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }

    PNGAutoClean autoClean(png_ptr, info_ptr);

    /* Set error handling if you are using the setjmp/longjmp method (this is
    * the normal method of doing things with libpng).  REQUIRED unless you
    * set up your own error handlers in the png_create_read_struct() earlier.
    */
    if (setjmp(png_jmpbuf(png_ptr))) {
        return false;
    }

    /* If you are using replacement read functions, instead of calling
    * png_init_io() here you would call:
    */
    png_set_read_fn(png_ptr, (void *)sk_stream, sk_read_fn);
    /* where user_io_ptr is a structure you want available to the callbacks */
    /* If we have already read some of the signature */
//  png_set_sig_bytes(png_ptr, 0 /* sig_read */ );

    // hookup our peeker so we can see any user-chunks the caller may be interested in
    png_set_keep_unknown_chunks(png_ptr, PNG_HANDLE_CHUNK_ALWAYS, (png_byte*)"", 0);
    if (this->getPeeker()) {
        png_set_read_user_chunk_fn(png_ptr, (png_voidp)this->getPeeker(), sk_read_user_chunk);
    }

    /* The call to png_read_info() gives us all of the information from the
    * PNG file before the first IDAT (image data chunk). */
    png_read_info(png_ptr, info_ptr);
    png_uint_32 origWidth, origHeight;
    int bit_depth, color_type, interlace_type;
    png_get_IHDR(png_ptr, info_ptr, &origWidth, &origHeight, &bit_depth, &color_type,
        &interlace_type, int_p_NULL, int_p_NULL);

    SkBitmap::Config    config;
    bool                hasAlpha = false;
    bool                doDither = this->getDitherImage();
    
    // check for sBIT chunk data, in case we should disable dithering because
    // our data is not truely 8bits per component
    if (doDither) {
#if 0
        SkDebugf("----- sBIT %d %d %d %d\n", info_ptr->sig_bit.red,
                 info_ptr->sig_bit.green, info_ptr->sig_bit.blue,
                 info_ptr->sig_bit.alpha);
#endif
        // 0 seems to indicate no information available
        if (pos_le(info_ptr->sig_bit.red, SK_R16_BITS) &&
                pos_le(info_ptr->sig_bit.green, SK_G16_BITS) &&
                pos_le(info_ptr->sig_bit.blue, SK_B16_BITS)) {
            doDither = false;
        }
    }
    
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        config = SkBitmap::kIndex8_Config;  // defer sniffing for hasAlpha
    } else {
        png_color_16p   transColor;
        
        png_get_tRNS(png_ptr, info_ptr, NULL, NULL, &transColor);
        
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) ||
                PNG_COLOR_TYPE_RGB_ALPHA == color_type ||
                PNG_COLOR_TYPE_GRAY_ALPHA == color_type) {
            hasAlpha = true;
            config = SkBitmap::kARGB_8888_Config;
        } else {    // we get to choose the config
            config = prefConfig;
            if (config == SkBitmap::kNo_Config) {
                config = SkImageDecoder::GetDeviceConfig();
            }
            if (config != SkBitmap::kRGB_565_Config &&
                    config != SkBitmap::kARGB_4444_Config) {
                config = SkBitmap::kARGB_8888_Config;
            }
        }
    }
    
    if (!this->chooseFromOneChoice(config, origWidth, origHeight)) {
        return false;
    }
    
    const int sampleSize = this->getSampleSize();
    SkScaledBitmapSampler sampler(origWidth, origHeight, sampleSize);

    decodedBitmap->setConfig(config, sampler.scaledWidth(),
                             sampler.scaledHeight(), 0);
    if (SkImageDecoder::kDecodeBounds_Mode == mode) {
        return true;
    }
    
    // from here down we are concerned with colortables and pixels

    /* tell libpng to strip 16 bit/color files down to 8 bits/color */
    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }
    /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
    * byte into separate bytes (useful for paletted and grayscale images). */
    if (bit_depth < 8) {
        png_set_packing(png_ptr);
    }
    /* Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel */
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_gray_1_2_4_to_8(png_ptr);
    }

    /* Make a grayscale image into RGB. */
    if (color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png_ptr);
    }

    // we track if we actually see a non-opaque pixels, since sometimes a PNG sets its colortype
    // to |= PNG_COLOR_MASK_ALPHA, but all of its pixels are in fact opaque. We care, since we
    // draw lots faster if we can flag the bitmap has being opaque
    bool reallyHasAlpha = false;

    SkColorTable* colorTable = NULL;

    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        int num_palette;
        png_colorp palette;
        png_bytep trans;
        int num_trans;

        png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
        
        /*  BUGGY IMAGE WORKAROUND
            
            We hit some images (e.g. fruit_.png) who contain bytes that are == colortable_count
            which is a problem since we use the byte as an index. To work around this we grow
            the colortable by 1 (if its < 256) and duplicate the last color into that slot.
        */
        int colorCount = num_palette + (num_palette < 256);

        colorTable = SkNEW_ARGS(SkColorTable, (colorCount));

        SkPMColor* colorPtr = colorTable->lockColors();
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
            png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, NULL);
            hasAlpha = (num_trans > 0);
        } else {
            num_trans = 0;
            colorTable->setFlags(colorTable->getFlags() | SkColorTable::kColorsAreOpaque_Flag);
        }        
        // check for bad images that might make us crash
        if (num_trans > num_palette) {
            num_trans = num_palette;
        }

        int index = 0;
        int transLessThanFF = 0;

        for (; index < num_trans; index++) {
            transLessThanFF |= (int)*trans - 0xFF;
            *colorPtr++ = SkPreMultiplyARGB(*trans++, palette->red, palette->green, palette->blue);
            palette++;
        }
        reallyHasAlpha |= (transLessThanFF < 0);

        for (; index < num_palette; index++) {
            *colorPtr++ = SkPackARGB32(0xFF, palette->red, palette->green, palette->blue);
            palette++;
        }

        // see BUGGY IMAGE WORKAROUND comment above
        if (num_palette < 256) {
            *colorPtr = colorPtr[-1];
        }
        colorTable->unlockColors(true);
    }
    
    SkAutoUnref aur(colorTable);

    if (!this->allocPixelRef(decodedBitmap, colorTable)) {
        delete colorTable;
        return false;
    }
    
    SkAutoLockPixels alp(*decodedBitmap);

    /* swap the RGBA or GA data to ARGB or AG (or BGRA to ABGR) */
//  if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
//      ; // png_set_swap_alpha(png_ptr);

    /* swap bytes of 16 bit files to least significant byte first */
    //   png_set_swap(png_ptr);

    /* Add filler (or alpha) byte (before/after each RGB triplet) */
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY) {
        png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
    }

    /* Turn on interlace handling.  REQUIRED if you are not using
    * png_read_image().  To see how to handle interlacing passes,
    * see the png_read_row() method below:
    */
    const int number_passes = interlace_type != PNG_INTERLACE_NONE ? 
                        png_set_interlace_handling(png_ptr) : 1;

    /* Optional call to gamma correct and add the background to the palette
    * and update info structure.  REQUIRED if you are expecting libpng to
    * update the palette for you (ie you selected such a transform above).
    */
    png_read_update_info(png_ptr, info_ptr);

    if (SkBitmap::kIndex8_Config == config && 1 == sampleSize) {
        for (int i = 0; i < number_passes; i++) {
            for (png_uint_32 y = 0; y < origHeight; y++) {
                uint8_t* bmRow = decodedBitmap->getAddr8(0, y);
                png_read_rows(png_ptr, &bmRow, png_bytepp_NULL, 1);
            }
        }
    } else {
        SkScaledBitmapSampler::SrcConfig sc;
        int srcBytesPerPixel = 4;
        
        if (SkBitmap::kIndex8_Config == config) {
            sc = SkScaledBitmapSampler::kIndex;
            srcBytesPerPixel = 1;
        } else if (hasAlpha) {
            sc = SkScaledBitmapSampler::kRGBA;
        } else {
            sc = SkScaledBitmapSampler::kRGBX;
        }

        SkAutoMalloc storage(origWidth * srcBytesPerPixel);
        const int height = decodedBitmap->height();

        for (int i = 0; i < number_passes; i++) {
            if (!sampler.begin(decodedBitmap, sc, doDither)) {
                return false;
            }

            uint8_t* srcRow = (uint8_t*)storage.get();
            skip_src_rows(png_ptr, srcRow, sampler.srcY0());

            for (int y = 0; y < height; y++) {
                uint8_t* tmp = srcRow;
                png_read_rows(png_ptr, &tmp, png_bytepp_NULL, 1);
                reallyHasAlpha |= sampler.next(srcRow);
                if (y < height - 1) {
                    skip_src_rows(png_ptr, srcRow, sampler.srcDY() - 1);
                }
            }
            
            // skip the rest of the rows (if any)
            png_uint_32 read = (height - 1) * sampler.srcDY() +
                               sampler.srcY0() + 1;
            SkASSERT(read <= origHeight);
            skip_src_rows(png_ptr, srcRow, origHeight - read);
        }

        if (hasAlpha && !reallyHasAlpha) {
            SkDEBUGF(("Image doesn't really have alpha [%d %d]\n",
                      origWidth, origHeight));
        }
    }

    /* read rest of file, and get additional chunks in info_ptr - REQUIRED */
    png_read_end(png_ptr, info_ptr);

    decodedBitmap->setIsOpaque(!reallyHasAlpha);
    return true;
}