bool scroll_widget::event(QEvent *a_event_ptr) {
  if (!o_scroll_widget->m_viewport) {
    return QGraphicsObject::event(a_event_ptr);
  }

  switch (a_event_ptr->type()) {
  case QScrollPrepareEvent::ScrollPrepare: {
    qDebug() << Q_FUNC_INFO << "Prepare :";
    QScrollPrepareEvent *se = static_cast<QScrollPrepareEvent *>(a_event_ptr);
    se->setViewportSize(o_scroll_widget->m_size);
    QRectF br = o_scroll_widget->m_viewport->boundingRect();
    se->setContentPosRange(QRectF(
        0, 0, qMax(qreal(0), br.width() - o_scroll_widget->m_size.width()),
        qMax(qreal(0), br.height() - o_scroll_widget->m_size.height())));
    se->setContentPos(-o_scroll_widget->m_viewport->pos());
    se->accept();
    return QGraphicsObject::event(a_event_ptr);
  }
  case QScrollEvent::Scroll: {
    qDebug() << Q_FUNC_INFO << "Scroll";
    QScrollEvent *se = static_cast<QScrollEvent *>(a_event_ptr);
    o_scroll_widget->m_viewport->setPos(-se->contentPos() -
                                        se->overshootDistance());
    return true;
  }

  default:
    break;
  }
  return QGraphicsObject::event(a_event_ptr);
}