void KstPlotGroup::paintSelf(KstPainter& p, const QRegion& bounds) {
  if (!transparent()) {
    p.save();
    // fill non-children areas with color
    QRegion clipRegion(contentsRect());
    QBrush brush(_backgroundColor);
    for (KstViewObjectList::Iterator i = _children.begin(); i != _children.end(); ++i) {
      clipRegion -= (*i)->clipRegion();
    }
    p.setClipRegion(clipRegion);
    p.fillRect(contentsRect(), brush);
    p.restore();
  }

  KstMetaPlot::paintSelf(p, bounds);
}