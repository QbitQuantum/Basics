QImage imageToQImage(const Image& image)
{
  const int cols = image.cols();
  const int rows = image.rows();
  QImage result(cols, rows, QImage::Format_RGB32);

  if (Image::PixelFormat::Gray8 == image.pixelFormat())
  {
    #pragma omp parallel for
    for (int y = 0; y < rows; ++y)
    {
      QRgb* dst = reinterpret_cast<QRgb*>(result.scanLine(y));
      for (int x = 0; x < cols; ++x)
      {
        const auto src = image.pixel<Gray8>(x, y);
        dst[x] = qRgb(src.g, src.g, src.g);
      }
    }
  }
  else if (Image::PixelFormat::RGBA8 == image.pixelFormat())
  {
    #pragma omp parallel for
    for (int y = 0; y < rows; ++y)
    {
      QRgb* dst = reinterpret_cast<QRgb*>(result.scanLine(y));
      for (int x = 0; x < cols; ++x)
      {
        const Rgba8& src = image.pixel<Rgba8>(x, y);
        dst[x] = qRgb(src.r, src.g, src.b);
      }
    }
  }
  else if (Image::PixelFormat::Float == image.pixelFormat())
  {
    AURORA_THROW(ENotSupported, "Float image are not supported");
  }
  else
  {
    AURORA_UNREACHABLE;
  }

  return result;
}