  void PixelMap::load(const Image &image)
  {
    clear();

    size = image.getSize();

    map = new u8*[size.getHeight()];

    for(int y = 0; y < size.getHeight(); y++)
    {
      int linelength;

      linelength = size.getWidth()%8 == 0 ? size.getWidth()/8 : size.getWidth()/8 + 1;

      map[y] = new u8[linelength];
        memset(map[y], 0, sizeof(*map[y]) * linelength);

      for(int x = 0; x < size.getWidth(); x++)
      {
        if(!image.hasColorkey())
          set_pixel(x, y, 1);
        else if(image.getPixel(IntPoint(x, y)) != image.getColorkey())
          set_pixel(x, y, 1);
      }
    }

  }