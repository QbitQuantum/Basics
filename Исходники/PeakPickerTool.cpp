void PeakPickerTool::draw(QPainter *p, const QwtScaleMap &xMap,
                          const QwtScaleMap &yMap, const QRect &) const {
  try {
    MantidQt::MantidWidgets::PropertyHandler *h =
        m_fitPropertyBrowser->getHandler();
    if (!h)
      return;
    QList<MantidQt::MantidWidgets::PropertyHandler *> peaks = h->getPeakList();
    foreach (MantidQt::MantidWidgets::PropertyHandler *peak, peaks) {
      double c = peak->centre();
      if (c >= xMap.s1() && c <= xMap.s2()) {
        int ic = xMap.transform(c);
        if (peak ==
            m_fitPropertyBrowser->currentHandler()) { // draw current peak
          double width = peak->fwhm();
          QPen pen;
          pen.setColor(QColor(255, 0, 0));
          pen.setStyle(Qt::DashLine);
          p->setPen(pen);
          int x1 = xMap.transform(c - width / 2);
          int x2 = xMap.transform(c + width / 2);
          QwtPainter::drawLine(p, x1, int(yMap.p1()), x1, int(yMap.p2()));
          QwtPainter::drawLine(p, x2, int(yMap.p1()), x2, int(yMap.p2()));

          pen.setStyle(Qt::SolidLine);
          p->setPen(pen);
          int ih = yMap.transform(peak->height() + peak->base());
          int ib = yMap.transform(peak->base());
          QwtPainter::drawLine(p, ic, ib, ic, ih);
          QwtPainter::drawLine(p, x1, ib, x2, ib);
        } else {
          p->setPen(QPen(QColor(200, 200, 200)));
          QwtPainter::drawLine(p, ic, int(yMap.p1()), ic, int(yMap.p2()));
        }
      }
    }
  } catch (...) {
    // Do nothing
  }
  QPen pen;
  pen.setColor(QColor(0, 0, 255));
  pen.setStyle(Qt::DashLine);
  p->setPen(pen);
  int x1 = xMap.transform(xMin());
  int x2 = xMap.transform(xMax());
  QwtPainter::drawLine(p, x1, int(yMap.p1()), x1, int(yMap.p2()));
  QwtPainter::drawLine(p, x2, int(yMap.p1()), x2, int(yMap.p2()));

  pen.setColor(QColor(0, 0, 255));
  pen.setStyle(Qt::SolidLine);
  p->setPen(pen);
  QwtPainter::drawLine(p, x1, int(yMap.p1()), x1 + 3, int(yMap.p1()));
  QwtPainter::drawLine(p, x1, int(yMap.p2()), x1 + 3, int(yMap.p2()));

  QwtPainter::drawLine(p, x2, int(yMap.p1()), x2 - 3, int(yMap.p1()));
  QwtPainter::drawLine(p, x2, int(yMap.p2()), x2 - 3, int(yMap.p2()));
}