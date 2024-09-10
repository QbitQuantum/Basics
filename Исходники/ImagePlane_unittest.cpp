TEST(ImagePlane, GetPixelByXY)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    for (std::size_t x = 0; x < plane.width(); x++)
    {
        for (std::size_t y = 0; y < plane.height(); y++)
        {
            EXPECT_EQ(plane.getPixel(x, y), lenaGray8[y * LENA_GRAY8_WIDTH + x]);
        }
    }
}