void encodeJpegIntoOutputStream(
    JNIEnv* env,
    DecodedImage& decoded_image,
    jobject os,
    int quality) {
  // jpeg does not support alpha channel
  THROW_AND_RETURN_IF(
      decoded_image.getPixelFormat() != PixelFormat::RGB,
      "Wrong pixel format for jpeg encoding");

  struct jpeg_compress_struct cinfo;

  // set up error handling
  JpegErrorHandler error_handler{env};
  error_handler.setCompressStruct(cinfo);
  if (setjmp(error_handler.setjmpBuffer)) {
    return;
  }

  // set up OutputStream as jpeg codec destination
  jpeg_create_compress(&cinfo);
  JpegOutputStreamWrapper os_wrapper{env, os};
  cinfo.dest = &(os_wrapper.public_fields);

  // set up image properties
  cinfo.image_width = decoded_image.getWidth();
  cinfo.image_height = decoded_image.getHeight();
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);
  jpeg_start_compress(&cinfo, TRUE);

  writeMetadata(cinfo, decoded_image);

  // write all pixels, row by row
  JSAMPROW row_pointer = decoded_image.getPixelsPtr();
  const int stride = decoded_image.getStride();
  while (cinfo.next_scanline < cinfo.image_height) {
    if (jpeg_write_scanlines(&cinfo, &row_pointer, 1) != 1) {
      jpegSafeThrow(
          (j_common_ptr) &cinfo,
          "Could not write scanline");
    }
    std::advance(row_pointer, stride);
  }

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
}