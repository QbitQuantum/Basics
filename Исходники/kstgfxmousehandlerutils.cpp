QRect KstGfxMouseHandlerUtils::resizeRectFromCorner(const QPoint& anchorPoint, const QPoint& movePoint, const QPoint& pos, const QRect& bounds, bool maintainAspect) {
  QRect newSize;
  QPoint npos = pos;

  if (maintainAspect) {
    QPoint fakeMovePoint = anchorPoint + QPoint(quadrantSign(pos,anchorPoint)*abs((movePoint - anchorPoint).x()),abs((movePoint - anchorPoint).y())); // allow the rectangle to flip.
    npos = findNearestPtOnLine(anchorPoint, fakeMovePoint, pos, bounds);
  }

  newSize.setTopLeft(anchorPoint);
  newSize.setBottomRight(npos);

  return bounds.intersect(newSize.normalize());
}