    void BWEffect(SDLSurface &surface) {
        static int x, y;
        static bool left, up;
        int width = int(surface.GetWidth()/3);
        int height = int(surface.GetHeight()/3);
        int delta = 2;

        if (!player.IsPaused()) {
            if (left)
                x -= delta;
            else
                x += delta;
            if (up)
                y -= delta;
            else
                y += delta;
            if (x < 0) {
                left = false;
                x = 1;
            } else if (x >= surface.GetWidth()-width) {
                left = true;
                x = surface.GetWidth()-width - 1;
            }
            if (y < 0) {
                up = false;
                y = 1;
            } else if (y >= surface.GetHeight()-height) {
                up = true;
                y = surface.GetHeight()-height - 1;
            }
        }
        for (int r = y; r < y+height; ++r) {
            for (int c = x; c < x+width; ++c) {
                byte bw = Grayscale(surface.GetPixel(c, r));
                surface.DrawPixel(c, r, Color(bw, bw, bw));
            }
        }
        surface.DrawRect(x, y, width, height, 1, Black());
    }