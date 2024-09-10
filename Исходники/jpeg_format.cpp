bool JpegFormat::onLoad(FileOp* fop)
{
    struct jpeg_decompress_struct cinfo;
    struct error_mgr jerr;
    JDIMENSION num_scanlines;
    JSAMPARRAY buffer;
    JDIMENSION buffer_height;
    int c;

    FileHandle handle(open_file_with_exception(fop->filename(), "rb"));
    FILE* file = handle.get();

    // Initialize the JPEG decompression object with error handling.
    jerr.fop = fop;
    cinfo.err = jpeg_std_error(&jerr.head);

    jerr.head.error_exit = error_exit;
    jerr.head.output_message = output_message;

    // Establish the setjmp return context for error_exit to use.
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        return false;
    }

    jpeg_create_decompress(&cinfo);

    // Specify data source for decompression.
    jpeg_stdio_src(&cinfo, file);

    // Read file header, set default decompression parameters.
    jpeg_read_header(&cinfo, true);

    if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
        cinfo.out_color_space = JCS_GRAYSCALE;
    else
        cinfo.out_color_space = JCS_RGB;

    // Start decompressor.
    jpeg_start_decompress(&cinfo);

    // Create the image.
    Image* image = fop->sequenceImage(
                       (cinfo.out_color_space == JCS_RGB ? IMAGE_RGB:
                        IMAGE_GRAYSCALE),
                       cinfo.output_width,
                       cinfo.output_height);
    if (!image) {
        jpeg_destroy_decompress(&cinfo);
        return false;
    }

    // Create the buffer.
    buffer_height = cinfo.rec_outbuf_height;
    buffer = (JSAMPARRAY)base_malloc(sizeof(JSAMPROW) * buffer_height);
    if (!buffer) {
        jpeg_destroy_decompress(&cinfo);
        return false;
    }

    for (c=0; c<(int)buffer_height; c++) {
        buffer[c] = (JSAMPROW)base_malloc(sizeof(JSAMPLE) *
                                          cinfo.output_width * cinfo.output_components);
        if (!buffer[c]) {
            for (c--; c>=0; c--)
                base_free(buffer[c]);
            base_free(buffer);
            jpeg_destroy_decompress(&cinfo);
            return false;
        }
    }

    // Generate a grayscale palette if is necessary.
    if (image->pixelFormat() == IMAGE_GRAYSCALE)
        for (c=0; c<256; c++)
            fop->sequenceSetColor(c, c, c, c);

    // Read each scan line.
    while (cinfo.output_scanline < cinfo.output_height) {
        // TODO
        /*     if (plugin_want_close())  */
        /*       break; */

        num_scanlines = jpeg_read_scanlines(&cinfo, buffer, buffer_height);

        // RGB
        if (image->pixelFormat() == IMAGE_RGB) {
            uint8_t* src_address;
            uint32_t* dst_address;
            int x, y, r, g, b;

            for (y=0; y<(int)num_scanlines; y++) {
                src_address = ((uint8_t**)buffer)[y];
                dst_address = (uint32_t*)image->getPixelAddress(0, cinfo.output_scanline-1+y);

                for (x=0; x<image->width(); x++) {
                    r = *(src_address++);
                    g = *(src_address++);
                    b = *(src_address++);
                    *(dst_address++) = rgba(r, g, b, 255);
                }
            }
        }
        // Grayscale
        else {
            uint8_t* src_address;
            uint16_t* dst_address;
            int x, y;

            for (y=0; y<(int)num_scanlines; y++) {
                src_address = ((uint8_t**)buffer)[y];
                dst_address = (uint16_t*)image->getPixelAddress(0, cinfo.output_scanline-1+y);

                for (x=0; x<image->width(); x++)
                    *(dst_address++) = graya(*(src_address++), 255);
            }
        }

        fop->setProgress((float)(cinfo.output_scanline+1) / (float)(cinfo.output_height));
        if (fop->isStop())
            break;
    }

    /* destroy all data */
    for (c=0; c<(int)buffer_height; c++)
        base_free(buffer[c]);
    base_free(buffer);

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return true;
}