void ImageCodecTiff::save(const Image& image, const std::string& filename)
{
  // create a new TIFF file
  Tiff::File file(TIFFOpen(filename.c_str(), "w"));

  if (!file)
    AURORA_THROW(EInOut, "File could not be created: " + filename);

  const int64_t cols = image.cols();
  const int64_t rows = image.rows();

  uint16_t samplesPerPixel;

  // some standard tags that must be set
  Tiff::setField(file, TIFFTAG_IMAGEWIDTH   , cols);
  Tiff::setField(file, TIFFTAG_IMAGELENGTH  , rows);
  Tiff::setField(file, TIFFTAG_BITSPERSAMPLE, 8);
  Tiff::setField(file, TIFFTAG_PLANARCONFIG , PLANARCONFIG_CONTIG);
  Tiff::setField(file, TIFFTAG_ROWSPERSTRIP , rows);

  if (Image::PixelFormat::Gray8 == image.pixelFormat())
  {
    samplesPerPixel = 1;
    Tiff::setField(file, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
  }
  else if (Image::PixelFormat::RGBA8 == image.pixelFormat())
  {
    samplesPerPixel = 3;
    Tiff::setField(file, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  }
  else if (Image::PixelFormat::Float == image.pixelFormat())
  {
    AURORA_THROW(ENotSupported, "Float images cannot be saved.");
  }
  else
  {
    AURORA_UNREACHABLE;
  }

  Tiff::setField(file, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);

  // convert the internal format into the TIFF format
  std::vector<uint8_t> tempBuffer(cols * rows * samplesPerPixel);

  if (Image::PixelFormat::Gray8 == image.pixelFormat())
  {
    #pragma omp parallel for
    for (int64_t y = 0; y < rows; ++y)
      for (int64_t x = 0; x < cols; ++x)
        tempBuffer[y * cols + x] = image.pixel<Gray8>(x, y);
  }
  else if (Image::PixelFormat::RGBA8 == image.pixelFormat())
  {
    #pragma omp parallel for
    for (int64_t y = 0; y < rows; ++y)
    {
      for (int64_t x = 0; x < cols; ++x)
      {
        tempBuffer[(y * cols + x) * 3 + 0] = image.pixel<Rgba8>(x, y).r;
        tempBuffer[(y * cols + x) * 3 + 1] = image.pixel<Rgba8>(x, y).g;
        tempBuffer[(y * cols + x) * 3 + 2] = image.pixel<Rgba8>(x, y).b;
      }
    }
  }
  else
  {
    AURORA_UNREACHABLE;
  }

  // write all the image data at once
  const int64_t numBytes = cols * rows * samplesPerPixel;
  if (-1 == TIFFWriteEncodedStrip(file, 0, tempBuffer.data(), numBytes))
    AURORA_THROW(EInOut, "Writing image data to TIFF file failed.");
}