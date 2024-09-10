bool AbstractWheelWidget::event(QEvent *e)
{
    switch (e->type()) {
// ![1]
    case QEvent::ScrollPrepare:
    {
        // We set the snap positions as late as possible so that we are sure
        // we get the correct itemHeight
        QScroller *scroller = QScroller::scroller(this);
        scroller->setSnapPositionsY( WHEEL_SCROLL_OFFSET, itemHeight() );

        QScrollPrepareEvent *se = static_cast<QScrollPrepareEvent *>(e);
        se->setViewportSize(QSizeF(size()));
        // we claim a huge scrolling area and a huge content position and
        // hope that the user doesn't notice that the scroll area is restricted
        se->setContentPosRange(QRectF(0.0, 0.0, 0.0, WHEEL_SCROLL_OFFSET * 2));
        se->setContentPos(QPointF(0.0, WHEEL_SCROLL_OFFSET + m_currentItem * itemHeight() + m_itemOffset));
        se->accept();
        return true;
    }
// ![1]
// ![2]
    case QEvent::Scroll:
    {
        QScrollEvent *se = static_cast<QScrollEvent *>(e);

        qreal y = se->contentPos().y();
        int iy = y - WHEEL_SCROLL_OFFSET;
        int ih = itemHeight();

// ![2]
// ![3]
        // -- calculate the current item position and offset and redraw the widget
        int ic = itemCount();
        if (ic>0) {
            m_currentItem = iy / ih % ic;
            m_itemOffset = iy % ih;

            // take care when scrolling backwards. Modulo returns negative numbers
            if (m_itemOffset < 0) {
                m_itemOffset += ih;
                m_currentItem--;
            }

            if (m_currentItem < 0)
                m_currentItem += ic;
        }
        // -- repaint
        update();

        se->accept();
        return true;
// ![3]
    }
    default:
        return QWidget::event(e);
    }
    return true;
}