bool Geometric2DCollection::Collides(const Triangle2D& t,int obstacle) const
{
  Type type=ObstacleType(obstacle);
  int index = ObstacleIndex(obstacle);
  switch(type) {
  case AABB:
    {
      Box2D box; box.set(aabbs[index]);
      return box.intersects(t);
    }
  case Triangle:
    return triangles[index].intersects(t);
  case Box:
    return boxes[index].intersects(t);
  case Circle:
    {
      return (t.closestPoint(circles[index].center).distanceSquared(circles[index].center) < Sqr(circles[index].radius));
    }
  }
  abort();
  return false;
}