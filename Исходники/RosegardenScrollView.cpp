void RosegardenScrollView::updateBottomWidgetGeometry()
{
    RG_DEBUG << "RosegardenScrollView::updateBottomWidgetGeometry" << endl;
    if (!m_bottomWidget)
        return ;

    int bottomWidgetHeight = m_bottomWidget->sizeHint().height();

    setContentsMargins(0, 0, 0, bottomWidgetHeight);
    QRect r = frameRect();
    int hScrollBarHeight = 0;
    if (horizontalScrollBar()->isVisible())
        hScrollBarHeight = horizontalScrollBar()->height() + 2; // + 2 offset needed to preserve border shadow

    int vScrollBarWidth = 0;
    if (verticalScrollBar()->isVisible())
        vScrollBarWidth = verticalScrollBar()->width();

    m_bottomWidget->setGeometry(r.x(),
                                r.y() + r.height() - bottomWidgetHeight - hScrollBarHeight,
                                r.width() - vScrollBarWidth,
                                bottomWidgetHeight);

    if (bottomWidgetHeight != m_currentBottomWidgetHeight) {
        emit bottomWidgetHeightChanged(bottomWidgetHeight);
        m_currentBottomWidgetHeight = bottomWidgetHeight;
    }

}