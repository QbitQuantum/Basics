void KstViewLabel::paintSelf(KstPainter& p, const QRegion& bounds) {
  p.save();
  if (p.type() == KstPainter::P_PRINT || p.type() == KstPainter::P_EXPORT) {
    int absFontSizeOld = _absFontSize;

    QRect cr(contentsRectForPainter(p));
    cr.setSize(sizeForText(_parent->geometry()));
    setContentsRectForPainter(p, cr);
    KstBorderedViewObject::paintSelf(p, bounds);

    p.translate(cr.left(), cr.top());
    if (!_transparent) {
      p.fillRect(0, 0, cr.width(), cr.height(), backgroundColor());
    }
    drawToPainter(_parsed, p);

    _absFontSize = absFontSizeOld;
  } else {
    if (p.makingMask()) {
      KstBorderedViewObject::paintSelf(p, bounds);
      p.setRasterOp(Qt::SetROP);
      const QRect cr(contentsRect());
      // slow but preserves antialiasing...
      QBitmap bm = _backBuffer.buffer().createHeuristicMask(false);
      bm.setMask(bm);
      p.drawPixmap(cr.left(), cr.top(), bm, 0, 0, cr.width(), cr.height());
    } else {
      const QRegion clip(clipRegion());
      KstBorderedViewObject::paintSelf(p, bounds);
      p.setClipRegion(bounds & clip);
      _backBuffer.paintInto(p, contentsRect());
    }
  }
  p.restore();
}