void ColorPicker::drawCrossAt(CPoint &point, CDC &dc, CSize &sz)
{
    CPoint localPoint = point;
    localPoint.x -= sz.cx / 2;
    localPoint.y -= sz.cy / 2;

    CRect localRect(localPoint, sz);
    dc.DrawEdge(localRect, EDGE_BUMP, BF_TOPLEFT | BF_BOTTOMRIGHT);
}