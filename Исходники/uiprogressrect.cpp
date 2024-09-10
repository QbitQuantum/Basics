void UIProgressRect::drawSelf(Fw::DrawPane drawPane)
{
    if((drawPane & Fw::ForegroundPane) == 0)
        return;

    g_painter->setColor(m_backgroundColor);

    // todo: check +1 to right/bottom
    // todo: add smooth
    Rect drawRect = getPaddingRect();

    // 0% - 12.5% (12.5)
    // triangle from top center, to top right (var x)
    if(m_percent < 12.5) {
        Point var = Point(std::max<int>(m_percent - 0.0, 0.0) * (drawRect.right() - drawRect.horizontalCenter()) / 12.5, 0);
        g_painter->drawFilledTriangle(drawRect.center(), drawRect.topRight() + Point(1,0), drawRect.topCenter() + var);
    }

    // 12.5% - 37.5% (25)
    // triangle from top right to bottom right (var y)
    if(m_percent < 37.5) {
        Point var = Point(0, std::max<int>(m_percent - 12.5, 0.0) * (drawRect.bottom() - drawRect.top()) / 25.0);
        g_painter->drawFilledTriangle(drawRect.center(), drawRect.bottomRight() + Point(1,1), drawRect.topRight() + var + Point(1,0));
    }

    // 37.5% - 62.5% (25)
    // triangle from bottom right to bottom left (var x)
    if(m_percent < 62.5) {
        Point var = Point(std::max<int>(m_percent - 37.5, 0.0) * (drawRect.right() - drawRect.left()) / 25.0, 0);
        g_painter->drawFilledTriangle(drawRect.center(), drawRect.bottomLeft() + Point(0,1), drawRect.bottomRight() - var + Point(1,1));
    }

    // 62.5% - 87.5% (25)
    // triangle from bottom left to top left
    if(m_percent < 87.5) {
        Point var = Point(0, std::max<int>(m_percent - 62.5, 0.0) * (drawRect.bottom() - drawRect.top()) / 25.0);
        g_painter->drawFilledTriangle(drawRect.center(), drawRect.topLeft(), drawRect.bottomLeft() - var + Point(0,1));
    }

    // 87.5% - 100% (12.5)
    // triangle from top left to top center
    if(m_percent < 100) {
        Point var = Point(std::max<int>(m_percent - 87.5, 0.0) * (drawRect.horizontalCenter() - drawRect.left()) / 12.5, 0);
        g_painter->drawFilledTriangle(drawRect.center(), drawRect.topCenter(), drawRect.topLeft() + var);
    }

    drawImage(m_rect);
    drawBorder(m_rect);
    drawIcon(m_rect);
    drawText(m_rect);
}