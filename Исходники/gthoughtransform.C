/*!
 * \brief Places a line into given rectangle
 * \param the line
 * \param the rectangle
 * \return QLineF beginning and ending at the edges of the rectangle.
 */
QLineF GT::intersectLineRect(const QLineF &st, const QRectF &rect) {
  QLineF start = st;
  QPointF iss[3];
  int i = 0;
  // Půlnoční velkorysý odhad:
  double longEnough = fabs(rect.bottom()) + fabs(rect.top()) + fabs(rect.left()) + fabs(rect.right()) + fabs(start.x1()) + fabs(start.x2()) + fabs(start.y1()) + fabs(start.y2());
  start.setLength(longEnough);
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.bottomLeft(),rect.bottomRight()), iss + i)) i++;
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.bottomLeft(),rect.topLeft()), iss + i)) i++;
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.topRight(),rect.bottomRight()), iss + i)) i++;
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.topRight(),rect.topLeft()), iss + i)) i++;

  start.setLength(-longEnough);
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.bottomLeft(),rect.bottomRight()), iss + i)) i++;
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.bottomLeft(),rect.topLeft()), iss + i)) i++;
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.topRight(),rect.bottomRight()), iss + i)) i++;
  if (QLineF::BoundedIntersection == start.intersect(QLineF(rect.topRight(),rect.topLeft()), iss + i)) i++;

  if (2 == i)
    return QLineF(iss[0],iss[1]);
  else return QLineF();
}