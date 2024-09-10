void HistogramItem::drawBar(QPainter *painter,
   Qt::Orientation, const QRect& rect) const
{
   painter->save();

   const QColor color(painter->pen().color());
#if QT_VERSION >= 0x040000
   const QRect r = rect.normalized();
#else
   const QRect r = rect.normalize();
#endif

   const int factor = 125;
   const QColor light(color.light(factor));
   const QColor dark(color.dark(factor));

   painter->setBrush(color);
   painter->setPen(Qt::NoPen);
   QwtPainter::drawRect(painter, r.x() + 1, r.y() + 1,
      r.width() - 2, r.height() - 2);
   painter->setBrush(Qt::NoBrush);

   painter->setPen(QPen(light, 2));
#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter,
      r.left() + 1, r.top() + 2, r.right() + 1, r.top() + 2);
#else
   QwtPainter::drawLine(painter,
      r.left(), r.top() + 2, r.right() + 1, r.top() + 2);
#endif

   painter->setPen(QPen(dark, 2));
#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter, 
      r.left() + 1, r.bottom(), r.right() + 1, r.bottom());
#else
   QwtPainter::drawLine(painter, 
      r.left(), r.bottom(), r.right() + 1, r.bottom());
#endif

   painter->setPen(QPen(light, 1));

#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter, 
      r.left(), r.top() + 1, r.left(), r.bottom());
   QwtPainter::drawLine(painter,
      r.left() + 1, r.top() + 2, r.left() + 1, r.bottom() - 1);
#else
   QwtPainter::drawLine(painter, 
      r.left(), r.top() + 1, r.left(), r.bottom() + 1);
   QwtPainter::drawLine(painter,
      r.left() + 1, r.top() + 2, r.left() + 1, r.bottom());
#endif

   painter->setPen(QPen(dark, 1));

#if QT_VERSION >= 0x040000
   QwtPainter::drawLine(painter, 
      r.right() + 1, r.top() + 1, r.right() + 1, r.bottom());
   QwtPainter::drawLine(painter, 
      r.right(), r.top() + 2, r.right(), r.bottom() - 1);
#else
   QwtPainter::drawLine(painter, 
      r.right() + 1, r.top() + 1, r.right() + 1, r.bottom() + 1);
   QwtPainter::drawLine(painter, 
      r.right(), r.top() + 2, r.right(), r.bottom());
#endif

   painter->restore();
}