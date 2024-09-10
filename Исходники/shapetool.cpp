void ShapeTool::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)

    QPainter painter;
    painter.begin(m_pDrawPadCanvas->currentPage()->pixmap());
    drawFinalShape(painter);
    painter.end();

    QRect r = m_polyline.boundingRect();
    r = r.normalize();
    r.setLeft(r.left() - m_pDrawPad->pen().width());
    r.setTop(r.top() - m_pDrawPad->pen().width());
    r.setRight(r.right() + m_pDrawPad->pen().width());
    r.setBottom(r.bottom() + m_pDrawPad->pen().width());

    QRect viewportRect(m_pDrawPadCanvas->contentsToViewport(r.topLeft()),
                       m_pDrawPadCanvas->contentsToViewport(r.bottomRight()));

    bitBlt(m_pDrawPadCanvas->viewport(), viewportRect.x(), viewportRect.y(),
           m_pDrawPadCanvas->currentPage()->pixmap(), r.x(), r.y(), r.width(), r.height());

    m_pDrawPadCanvas->viewport()->update(viewportRect);

    m_mousePressed = false;
}