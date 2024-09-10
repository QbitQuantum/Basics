m2::RectF StipplePenPacker::MapTextureCoords(m2::RectU const & pixelRect) const
{
    return m2::RectF((pixelRect.minX() + 1.0f) / m_canvasSize.x,
                     (pixelRect.minY() + 1.0f) / m_canvasSize.y,
                     (pixelRect.maxX() - 1.0f) / m_canvasSize.x,
                     (pixelRect.maxY() - 1.0f) / m_canvasSize.y);
}