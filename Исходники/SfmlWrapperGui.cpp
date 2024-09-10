void SfmlWrapperGui::drawBuffer(Point<int> const &position, Buffer<unsigned char> const &buffer)
{
  size_t x = 0;
  size_t y = -1;
  size_t width = buffer.getWidth();
  size_t height = buffer.getHeight();

  while (++y < height)
  {
    x = -1;
    while (++x < width)
    {
      Color<unsigned char> color = buffer.getPixel(x, y);
      sf::Color sfcolor(color.getRed(), color.getGreen(), color.getBlue());
      _image->setPixel(position.getX() + x, position.getY() + y, sfcolor);
    }
  }
}