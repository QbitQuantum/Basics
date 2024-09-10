    void PotraceImage::InvertPixels(const vector<Point2>& pixels) {
        vector<Point2>::const_iterator it;
        const vector<Point2>::const_iterator pixelsEnd = pixels.end();
        for (it = pixels.begin(); it != pixelsEnd; ++it) {
            if (it->x >= 0 && it->x < GetW() || it->y >= 0 || it->y < GetH()) {
                long mapIndex = it->y * GetW() + it->x;

                PixelColor::Enum currentColor = pixelMap[mapIndex];
                PixelColor::Enum invertedColor = (currentColor == PixelColor::Black ? PixelColor::White : PixelColor::Black);
                
                pixelMap[mapIndex] = invertedColor;
                isInvertedMap[mapIndex] = !isInvertedMap[mapIndex];
            }
        }
    }