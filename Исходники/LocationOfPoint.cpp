WayLocation LocationOfPoint::locateAfter(const Coordinate& inputPt, const WayLocation& minLocation)
    const
{
  if (minLocation.isValid() == false)
  {
    return locate(inputPt);
  }

  assert(minLocation.getWay() == _way);

  double minDistance = std::numeric_limits<double>().max();
  WayLocation nextClosestLocation = minLocation;

  LineSegment seg;
  size_t startIndex = 0;
  startIndex = (size_t)minLocation.getSegmentIndex();

  for (size_t i = startIndex; i < _way->getNodeCount() - 1; i++)
  {
    seg.p0 = _map->getNode(_way->getNodeId(i))->toCoordinate();
    seg.p1 = _map->getNode(_way->getNodeId(i + 1))->toCoordinate();

    if (i == startIndex)
    {
      seg.p0 = minLocation.getCoordinate();
    }

    double segDistance = seg.distance(inputPt);
    double segFrac = segmentFraction(seg, inputPt);

    if (segDistance < minDistance)
    {
      // if this is the first case (a partial line segment)
      if (i == startIndex)
      {
        // recalculate the segFrac in terms of the whole line segment.
        segFrac = minLocation.getSegmentFraction() +
            (1 - minLocation.getSegmentFraction()) * segFrac;
      }
      nextClosestLocation = WayLocation(_map, _way, i, segFrac);
      minDistance = segDistance;
    }
  }
  // Return the minDistanceLocation found.
  // This will not be null, since it was initialized to minLocation
  Assert::isFalse(nextClosestLocation >= minLocation,
                "computed location is before specified minimum location");

  return nextClosestLocation;
}