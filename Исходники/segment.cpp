Vec2D Segment::intersectionPoint(Segment const& other) const
{
  Vec2D selfDelta = delta();
  Vec2D otherDelta = other.delta();

  if(selfDelta.cross(otherDelta) != 0)
  {
    float t = other.a.subtract(a).cross(otherDelta) / selfDelta.cross(otherDelta);
    float u = other.a.subtract(a).cross(selfDelta) / selfDelta.cross(otherDelta);
    if(t >= 0 && t <= 1 && u >= 0 && u <= 1)
    {
      return a.add(selfDelta.scale(t));
    }
  }

  return Vec2D(0, 0);
}