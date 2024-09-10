void pp::getColors(cinder::Surface& source, Palette& result)
{
    result.clear();
    ivec2 v(0, 0);
    int width = source.getWidth();
    int height = source.getHeight();
    for (v.x = 0; v.x < width; v.x++)
        for (v.y = 0; v.y < height; v.y++)
        {
            Color8u pxl = source.getPixel(v);
            bool found = false;
            for (Palette::iterator it = result.begin(); it != result.end(); it++)
                if (distance2(Color8u(it->r, it->g, it->b), pxl) == 0)  // found
                    found = true;
            if (!found)
                result.push_back(pxl);
        }
}