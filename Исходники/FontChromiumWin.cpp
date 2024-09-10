void Font::drawComplexText(GraphicsContext* graphicsContext,
    const TextRunPaintInfo& runInfo,
    const FloatPoint& point) const
{
    UniscribeHelperTextRun state(runInfo.run, *this);

    SkColor color = graphicsContext->effectiveFillColor();
    unsigned char alpha = SkColorGetA(color);
    // Skip 100% transparent text; no need to draw anything.
    if (!alpha && graphicsContext->strokeStyle() == NoStroke)
        return;

    HDC hdc = 0;
    // Uniscribe counts the coordinates from the upper left, while WebKit uses
    // the baseline, so we have to subtract off the ascent.
    state.draw(graphicsContext, primaryFont()->platformData(), hdc, lroundf(point.x()), lroundf(point.y() - fontMetrics().ascent()), runInfo.bounds, runInfo.from, runInfo.to);
}