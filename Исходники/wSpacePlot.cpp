void WSpacePlot::selectRectTmp(const QRect &rect, bool select) {
  QRect r=rect.normalize();
  if (select)
    for (int x=r.left(); x<=r.right(); x++)
      for (int y=r.top(); y<=r.bottom(); y++)
	cellData[x+y*viewSize.width()].attr|=tmpSelected;
  else
    for (int x=r.left(); x<=r.right(); x++)
      for (int y=r.top(); y<=r.bottom(); y++)
	cellData[x+y*viewSize.width()].attr&=normal|marked;
}