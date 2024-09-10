Pixel
CwmCustomIcon::
getBgPixel(CwmScreen &screen) const
{
  std::string bg_color = getBg();

  return screen.getPixel(bg_color, screen.getWhitePixel());
}