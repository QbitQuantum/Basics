    void paintImage(Image<PixelType>& image) {
        auto width = image.getWidth();
        auto height = image.getHeight();
        auto pixels = getPixelsToPaint(width, height);

        for (auto x = 0u; x < width; ++x) {
            for (auto y = 0u; y < height; ++y)
                image.setPixel(x, y, pixels(x, y));
        }
    }