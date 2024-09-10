uint QColormap::pixel(const QColor &color) const
{
    const QColor c = color.toRgb();
    COLORREF rgb = RGB(c.red(), c.green(), c.blue());
    if (d->hpal)
        return PALETTEINDEX(GetNearestPaletteIndex(d->hpal, rgb));
    return rgb;
}