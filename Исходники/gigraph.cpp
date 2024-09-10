GiColor GiGraphics::calcPenColor(const GiColor& color) const
{
    GiColor ret = color;

    if (kColorMono == m_impl->colorMode)
    {
        const GiColor& bk = getBkColor();
        if (color != bk)
            ret.set(~bk.r, ~bk.g, ~bk.b);
    }
    if (m_impl->drawColors == 2           // 黑白
        || kColorGray == m_impl->colorMode)
    {
        unsigned char by = (unsigned char)(
            (77 * ret.r + 151 * ret.g + 28 * ret.b + 128) / 256);
        ret.set(by, by, by);
    }
    if (m_impl->drawColors > 0 && m_impl->drawColors < 8
        && m_impl->canvas)              // 少于256色
    {
        ret = m_impl->canvas->getNearestColor(ret);
    }

    return ret;
}