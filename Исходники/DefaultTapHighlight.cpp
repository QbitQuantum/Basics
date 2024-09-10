void DefaultTapHighlight::paintContents(const GraphicsLayer*, GraphicsContext& c, GraphicsLayerPaintingPhase, const IntRect& /*inClip*/)
{
    if (!m_region.numRects())
        return;

    Path path(m_region.boundaryPath());

    c.save();
    const Platform::IntRect& rect = m_region.extents();
    c.translate(-rect.x(), -rect.y());

    // Draw tap highlight
    c.setFillColor(m_color, ColorSpaceDeviceRGB);
    c.fillPath(path);
    Color darker = Color(m_color.red(), m_color.green(), m_color.blue()); // Get rid of alpha.
    c.setStrokeColor(darker, ColorSpaceDeviceRGB);
    c.setStrokeThickness(1);
    c.strokePath(path);
    c.restore();
}