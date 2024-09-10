QPolygonF polygonFromPath(potrace_path_t *path,
                          int bezierPrecision)
{
  QPolygonF poly;
  if(!path) return poly;

  int n = path->curve.n;
  int *tag = path->curve.tag;
  potrace_dpoint_t (*c)[3] = path->curve.c;
  for(int i = 0; i < n; ++i)
  {
    switch (tag[i])
    {
    case POTRACE_CORNER:
      poly << QPointF(c[i][1].x, c[i][1].y)
           << QPointF(c[i][2].x, c[i][2].y);
      break;
    case POTRACE_CURVETO:
    {
      QPointF pa, pb, pc, pd;
      pa = poly.isEmpty()? QPointF(c[n-1][2].x, c[n-1][2].y) :
                           poly.last();
      pb = QPointF(c[i][0].x, c[i][0].y);
      pc = QPointF(c[i][1].x, c[i][1].y);
      pd = QPointF(c[i][2].x, c[i][2].y);
      for(int i = 1; i <= bezierPrecision; ++i)
      {
        poly << bezier(pa, pb, pc, pd, static_cast<qreal>(i)/bezierPrecision);
      }
    }
      break;
    }
  }

  if(!poly.isEmpty() && poly.first() == poly.last())
  {
    poly.remove(poly.size()-1);
  }

  return poly;
}