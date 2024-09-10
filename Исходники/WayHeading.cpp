Coordinate WayHeading::calculateVector(const WayLocation& loc, Meters delta)
{
  Coordinate sc = loc.move(-delta).getCoordinate();
  Coordinate ec = loc.move(delta).getCoordinate();

  Coordinate result;
  result.x = ec.x - sc.x;
  result.y = ec.y - sc.y;

  double mag = result.distance(Coordinate(0, 0));
  result.x /= mag;
  result.y /= mag;

  return result;
}