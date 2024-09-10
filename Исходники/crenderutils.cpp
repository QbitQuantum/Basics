void drawAABB(const AABB    &t, unsigned TINT)
{
    sfw::drawLine(t.min().x, t.min().y, t.max().x ,t.min().y, TINT);
    sfw::drawLine(t.min().x, t.max().y, t.max().x, t.max().y, TINT);
    sfw::drawLine(t.max().x, t.min().y, t.max().x, t.max().y, TINT);
    sfw::drawLine(t.min().x, t.min().y, t.min().x, t.max().y, TINT);
}