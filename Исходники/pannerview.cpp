void PannerView::drawForeground(QPainter * p, const QRectF & rect )
{
  if (m_zoomRect.isValid() && rect.intersects(m_zoomRect))
  {
    p->save();
    if (m_zoomRect.width() > 10 && m_zoomRect.height() > 10)
    {
      p->setPen(Qt::red);
      // substract pen width, i.e. draw inside
      qreal penWidth = p->pen().widthF();
      p->drawRect(m_zoomRect.adjusted(-penWidth, -penWidth, -penWidth, -penWidth));
    }
    else
    {
      QBrush brush(Qt::red);
      p->fillRect(m_zoomRect, brush);
    }
    p->restore();
  }
}