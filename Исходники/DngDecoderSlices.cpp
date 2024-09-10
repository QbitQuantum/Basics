void DngDecoderSlices::decodeSlice(DngDecoderThread* t) {
  if (compression == 7) {
    while (!t->slices.empty()) {
      LJpegPlain l(mFile, mRaw);
      l.mDNGCompatible = mFixLjpeg;
      DngSliceElement e = t->slices.front();
      l.mUseBigtable = e.mUseBigtable;
      t->slices.pop();
      try {
        l.startDecoder(e.byteOffset, e.byteCount, e.offX, e.offY);
      } catch (RawDecoderException &err) {
        mRaw->setError(err.what());
      } catch (IOException &err) {
        mRaw->setError(err.what());
      }
    }
    /* Lossy DNG */
  } else if (compression == 0x884c) {
    /* Each slice is a JPEG image */
    struct jpeg_decompress_struct dinfo;
    struct jpeg_error_mgr jerr;
    while (!t->slices.empty()) {
      DngSliceElement e = t->slices.front();
      t->slices.pop();
      uchar8 *complete_buffer = NULL;
      JSAMPARRAY buffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW));

      try {
        uint32 size = mFile->getSize();
        jpeg_create_decompress(&dinfo);
        dinfo.err = jpeg_std_error(&jerr);
        jerr.error_exit = my_error_throw;
        CHECKSIZE(e.byteOffset);
        CHECKSIZE(e.byteOffset+e.byteCount);
        JPEG_MEMSRC(&dinfo, (unsigned char*)mFile->getData(e.byteOffset, e.byteCount), e.byteCount);

        if (JPEG_HEADER_OK != jpeg_read_header(&dinfo, TRUE))
          ThrowRDE("DngDecoderSlices: Unable to read JPEG header");

        jpeg_start_decompress(&dinfo);
        if (dinfo.output_components != (int)mRaw->getCpp())
          ThrowRDE("DngDecoderSlices: Component count doesn't match");
        int row_stride = dinfo.output_width * dinfo.output_components;
        int pic_size = dinfo.output_height * row_stride;
        complete_buffer = (uchar8*)_aligned_malloc(pic_size, 16);
        while (dinfo.output_scanline < dinfo.output_height) {
          buffer[0] = (JSAMPROW)(&complete_buffer[dinfo.output_scanline*row_stride]);
          if (0 == jpeg_read_scanlines(&dinfo, buffer, 1))
            ThrowRDE("DngDecoderSlices: JPEG Error while decompressing image.");
        }
        jpeg_finish_decompress(&dinfo);

        // Now the image is decoded, and we copy the image data
        int copy_w = min(mRaw->dim.x-e.offX, dinfo.output_width);
        int copy_h = min(mRaw->dim.y-e.offY, dinfo.output_height);
        for (int y = 0; y < copy_h; y++) {
          uchar8* src = &complete_buffer[row_stride*y];
          ushort16* dst = (ushort16*)mRaw->getData(e.offX, y+e.offY);
          for (int x = 0; x < copy_w; x++) {
            for (int c=0; c < dinfo.output_components; c++)
              *dst++ = (*src++);
          }
        }
      } catch (RawDecoderException &err) {
        mRaw->setError(err.what());
      } catch (IOException &err) {
        mRaw->setError(err.what());
      }
      free(buffer);
      if (complete_buffer)
        _aligned_free(complete_buffer);
      jpeg_destroy_decompress(&dinfo);
    }
  }
  else
    mRaw->setError("DngDecoderSlices: Unknown compression");
}