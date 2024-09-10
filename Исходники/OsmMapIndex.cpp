long OsmMapIndex::findNearestWay(Coordinate c) const
{
  long result = 0;
  double bestDistance = std::numeric_limits<double>::max();

  // grab the geometry for the way that we're comparing all others against.
  Point* p = GeometryFactory::getDefaultInstance()->createPoint(c);

  // go through all other ways
  for (WayMap::const_iterator it = _map.getWays().begin();
    it != _map.getWays().end(); ++it)
  {
    long nId = it->first;
    shared_ptr<const Way> n = it->second;
    if (n != 0 && n->getNodeCount() > 1)
    {
      shared_ptr<LineString> ls2 = ElementConverter(_map.shared_from_this()).convertToLineString(n);
      Meters d = p->distance(ls2.get());

      if (d < bestDistance)
      {
        result = nId;
        bestDistance = d;
      }
    }
  }

  delete p;

  return result;
}