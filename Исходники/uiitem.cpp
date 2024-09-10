void UIItem::drawSelf(Fw::DrawPane drawPane)
{
    if((drawPane & Fw::ForegroundPane) == 0)
        return;

    // draw style components in order
    if(m_backgroundColor.aF() > Fw::MIN_ALPHA) {
        Rect backgroundDestRect = m_rect;
        backgroundDestRect.expand(-m_borderWidth.top, -m_borderWidth.right, -m_borderWidth.bottom, -m_borderWidth.left);
        drawBackground(m_rect);
    }

    drawImage(m_rect);

    if(m_itemVisible && m_item) {
        Rect drawRect = getPaddingRect();
        Point dest = drawRect.bottomRight() + Point(1,1);

        int exactSize = std::max<int>(32, m_item->getExactSize());
        if(exactSize == 0)
            return;

        float scaleFactor = std::min<float>(drawRect.width() / (float)exactSize, drawRect.height() / (float)exactSize);
        dest += (m_item->getDisplacement() - Point(32,32)) * scaleFactor;

        g_painter->setColor(m_color);
        m_item->draw(dest, scaleFactor, true);

        if(m_font && (m_item->isStackable() || m_item->isChargeable()) && m_item->getCountOrSubType() > 1) {
            std::string count = stdext::to_string(m_item->getCountOrSubType());
            g_painter->setColor(Color(231, 231, 231));
            m_font->drawText(count, Rect(m_rect.topLeft(), m_rect.bottomRight() - Point(3, 0)), Fw::AlignBottomRight);
        }

        if(m_showId)
            m_font->drawText(stdext::to_string(m_item->getServerId()), m_rect, Fw::AlignBottomRight);
    }

    drawBorder(m_rect);
    drawIcon(m_rect);
    drawText(m_rect);
}