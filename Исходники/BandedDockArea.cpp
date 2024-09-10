void BandedDockArea::drawXorTracker(Graphics& g, DockInfo* _dockInfo)
{
  BandedDockInfo* dockInfo = static_cast<BandedDockInfo*>(_dockInfo);
  Rect bounds = getAbsoluteClientBounds();
  Rect externRect;
  Rect internRect;

  externRect = getBandBounds(dockInfo->band);

  if (isHorizontal()) {
    // size of the last band
    if (getSide() == Side::Bottom)
      externRect.y -= max_value(externRect.h, dockInfo->size.h) - externRect.h;

    externRect.h = max_value(externRect.h, dockInfo->size.h);
    internRect = Rect(Point(externRect.x + dockInfo->offset, externRect.y),
		      dockInfo->size);
  }
  else {
    // size of the last band
    if (getSide() == Side::Right)
      externRect.x -= max_value(externRect.w, dockInfo->size.w) - externRect.w;

    externRect.w = max_value(externRect.w, dockInfo->size.w);
    internRect = Rect(Point(externRect.x, externRect.y + dockInfo->offset),
		      dockInfo->size);
  }

  externRect.offset(bounds.getOrigin());
  internRect.offset(bounds.getOrigin());

  if (internRect.x < externRect.x) internRect.x = externRect.x;
  if (internRect.y < externRect.y) internRect.y = externRect.y;
  if (internRect.x+internRect.w > externRect.x+externRect.w) internRect.x = externRect.x+externRect.w-internRect.w;
  if (internRect.y+internRect.h > externRect.y+externRect.h) internRect.y = externRect.y+externRect.h-internRect.h;

  g.setRop2(R2_NOTXORPEN);
  Pen pen(Color::Black);	// TODO it's necessary... maybe XorPen?
//   g.drawRect(pen, externRect);
//   g.drawRect(pen, internRect.shrink(1));
  g.drawRect(pen, internRect);
  g.setRop2(R2_COPYPEN);
}