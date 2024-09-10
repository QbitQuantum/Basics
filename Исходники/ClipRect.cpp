bool ClipRect::intersects(const HitTestLocation& hitTestLocation) const
{
    return hitTestLocation.intersects(m_rect);
}