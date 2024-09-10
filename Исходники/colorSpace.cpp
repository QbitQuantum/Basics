float ColorSpace::getH()
{
    float h;
    if (getC() == 0.0f)
    {
        return 0.5f;
    }
    if (red == getZ())
    {
        h = ((float)(grn - blue) / getC() + 6.0f);
        while (h > 6.0f)
        {
            h = h - 6.0f;
        }
    } else if (grn == getZ())
    {
        h = (blue - red) / getC() + 2.0f;
    } else {
        h = (red - grn) / getC() + 4.0f;
    }
    return h / 6.0f;
}