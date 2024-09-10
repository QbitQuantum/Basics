long WayAverager::_moveToLine(long ni, double nWeight, const LineString* ls, double lWeight,
  int w1OrW2)
{
  shared_ptr<Node> n = _map.getNode(ni);
  Coordinate c = _moveToLineAsCoordinate(ni, nWeight, ls, lWeight);

  Meters d = c.distance(n->toCoordinate());
  if (w1OrW2 == 1)
  {
    _sumMovement1 += d;
    _moveCount1++;
    _maxMovement1 = max(_maxMovement1, d);
  }
  else
  {
    _sumMovement2 += d;
    _moveCount2++;
    _maxMovement2 = max(_maxMovement2, d);
  }


  n->setX(c.x);
  n->setY(c.y);

  return ni;
}