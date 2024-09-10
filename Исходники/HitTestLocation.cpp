bool HitTestLocation::intersects(const RoundedRect& rect) const
{
    return rect.intersectsQuad(m_transformedRect);
}