void Histogram::Autocontrast(const Image& src, Image& dst) {
  const int min = GetMin();
  const int max = GetMax();
  const int diff = max - min;
  const float fac = 255.0 / diff;
  
  if (diff == 0)
    return;

  for (int x = 0; x < src.GetWidth(); x++) {
    for (int y = 0; y < src.GetHeight(); y++) {
      unsigned char new_val = static_cast<unsigned char>(fac * (src.GetPixel(x, y, 2) - min));
      dst.SetPixel(x, y, 2, new_val);
    }
  }
}