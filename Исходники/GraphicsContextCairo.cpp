void GraphicsContext::fillRectWithRoundedHole(const IntRect& rect, const RoundedRect& roundedHoleRect, const Color& color, ColorSpace)
{
    if (paintingDisabled() || !color.isValid())
        return;

    if (this->mustUseShadowBlur())
        platformContext()->shadowBlur().drawInsetShadow(this, rect, roundedHoleRect.rect(), roundedHoleRect.radii());

    Path path;
    path.addRect(rect);
    if (!roundedHoleRect.radii().isZero())
        path.addRoundedRect(roundedHoleRect);
    else
        path.addRect(roundedHoleRect.rect());

    cairo_t* cr = platformContext()->cr();
    cairo_save(cr);
    setPathOnCairoContext(platformContext()->cr(), path.platformPath()->context());
    fillCurrentCairoPath(this);
    cairo_restore(cr);
}