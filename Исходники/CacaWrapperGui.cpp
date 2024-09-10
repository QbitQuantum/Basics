void CacaWrapperGui::drawBuffer(Point<int> const &point,
                                Buffer<unsigned char> const &buffer) {
    size_t width = buffer.getWidth();
    size_t height = buffer.getHeight();
    int nbPixBuff = 0;
    uint32_t moyR = 0;
    uint32_t moyG = 0;
    uint32_t moyB = 0;
    uint16_t color;

    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            Color<unsigned char> color = buffer.getPixel(j, i);
            moyR += color.getRed() / (255 / 16);
            moyB += color.getBlue() / (255 / 16);
            moyG += color.getGreen() / (255 / 16);
            nbPixBuff++;
        }
    }
    moyR /= nbPixBuff;
    moyB /= nbPixBuff;
    moyG /= nbPixBuff;
    color = 15;
    color <<= 4;
    color += moyR;
    color <<= 4;
    color += moyG;
    color <<= 4;
    color += moyB;
    moyG %= 26;

    caca_set_color_argb(_cv, color, CACA_BLACK);
    caca_put_char(_cv, point.getX() / MAP_TILE, point.getY() / MAP_TILE, moyG + 'A');
}