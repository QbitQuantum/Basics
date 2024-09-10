  bool ImageCodecJPEG::write(const Image & image, FILE * file)
  {
    int quality = 100;

    struct jpeg_error_mgr jerr;
    struct jpeg_compress_struct cinfo;

    // Set error handler first
    cinfo.err = jpeg_std_error(&jerr);

    // Init compression object
    jpeg_create_compress(&cinfo);

    // Set destination
    jpeg_stdio_dest(&cinfo, file);

    // Parameters
    cinfo.image_width = image.width();
    cinfo.image_height = image.height(); 
    cinfo.input_components = image.pixelFormat().numChannels();

    if(cinfo.input_components == 1) {
      cinfo.in_color_space = JCS_GRAYSCALE;
    } else if(cinfo.input_components == 3) {
      cinfo.in_color_space = JCS_RGB;
    } else {
      Radiant::error("ImageCodecJPEG::write # JPEG format only supports GRAYSCALE or RGB images");
      jpeg_destroy_compress(&cinfo);
      return false;
    }

    if(image.pixelFormat().type() != PixelFormat::TYPE_UBYTE) {
      Radiant::error("ImageCodecJPEG::write # JPEG only supports byte-based components");
      jpeg_destroy_compress(&cinfo);
      return false;
    }

    // Default compression parameters
    jpeg_set_defaults(&cinfo);

    // Set quality
    jpeg_set_quality(&cinfo, quality, TRUE);

    // Start compressing
    jpeg_start_compress(&cinfo, TRUE);

    int stride = image.width() * cinfo.input_components;

    // Write scanlines
    while(cinfo.next_scanline < cinfo.image_height) {
      unsigned char * buf = const_cast<unsigned char *> (image.bytes());
      buf = buf + cinfo.next_scanline * stride;
      JSAMPROW row_pointer = buf;
      jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    // Finish compression
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return true;
  }