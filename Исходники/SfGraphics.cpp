static void Image_setPixel(
    sf::Image& img, unsigned x, unsigned y, sf::Color c)
{
    if (x >= img.getSize().x || y >= img.getSize().y)
        throw "pixel coordinates of image out of range (@set)";
    img.setPixel(x, y, c);
}