WayLocation WayLocation::move(Meters distance) const
{
  WayLocation result(*this);
  Coordinate last = result.getCoordinate();

  // This odd statement avoid us adding irrelevantly small distances.
  while (1 + distance > 1)
  {
    // if we're at the end of the way
    if (result.isLast())
    {
      return result;
    }

    ConstNodePtr n = _map->getNode(_way->getNodeId(result.getSegmentIndex() + 1));
    Coordinate next = n->toCoordinate();

    double delta = last.distance(next);

    // if the next node is too far
    if (distance - delta < 0)
    {
      // figure out what distance we need to move along the segment.
      Coordinate lastSegment = _map->getNode(_way->getNodeId(result.getSegmentIndex()))->
          toCoordinate();
      double segmentLength = lastSegment.distance(next);
      result._segmentFraction += (distance / segmentLength);

      // this can happen due to floating point errors when the new location is very close to a
      // node.
      if (result._segmentFraction >= 1.0)
      {
        result._segmentFraction = 0.0;
        result._segmentIndex = result._segmentIndex + 1;
      }

      distance = 0;
    }
    // if we need to go past the next node
    else
    {
      distance -= delta;
      last = next;
      result._segmentIndex = result.getSegmentIndex() + 1;
      result._segmentFraction = 0.0;
    }
  }

  // This odd statement avoid us subtracting irrelevantly small distances.
  while (1 + distance < 1)
  {
    // if we're at the end of the way
    if (result.isFirst())
    {
      return result;
    }

    if (result._segmentFraction > 0)
    {
      Coordinate next = _map->getNode(_way->getNodeId(result.getSegmentIndex()))->toCoordinate();

      Meters delta = last.distance(next);
      if (distance + delta > 0)
      {
        // figure out what distance we need to move along the segment.
        Coordinate last = _map->getNode(_way->getNodeId(result._segmentIndex + 1))->toCoordinate();
        double segmentLength = last.distance(next);
        result._segmentFraction += (distance / segmentLength);

        // this can happen due to floating point errors when the new location is very close to a
        // node.
        if (result._segmentFraction >= 1.0)
        {
          result._segmentFraction = 0.0;
          result._segmentIndex = result._segmentIndex + 1;
        }

        distance = 0;
      }
      else
      {
        result._segmentFraction = 0;
        distance += delta;
        last = next;
      }
    }
    else
    {
      Coordinate next = _map->getNode(_way->getNodeId(result.getSegmentIndex() - 1))->
          toCoordinate();

      Meters delta = last.distance(next);
      if (distance + delta > 0)
      {
        // figure out what distance we need to move along the segment.
        Coordinate last = _map->getNode(_way->getNodeId(result.getSegmentIndex()))->toCoordinate();
        double segmentLength = last.distance(next);
        result._segmentFraction = 1.0 + (distance / segmentLength);
        // if we're suffering from a floating point issue.
        if (result._segmentFraction >= 1.0)
        {
          // make sure the floating point issue is within the expected bounds.
          assert(result._segmentFraction < 1.0 + 1e-14);
          result._segmentFraction = 0;
        }
        else
        {
          result._segmentIndex = result.getSegmentIndex() - 1;
        }
        distance = 0;
      }
      else
      {
        result._segmentIndex--;
        distance += delta;
        last = next;
      }
    }
  }

  assert(result._segmentFraction < 1.0 && result._segmentFraction >= 0);
  assert(result._segmentIndex >= 0 && result._segmentIndex < (int)result.getWay()->getNodeCount());

  return result;
}