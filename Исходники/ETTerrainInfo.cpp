  std::pair<bool, Vector3> TerrainInfo::rayIntersects(const Ray& ray) const
  {
    AxisAlignedBox box = getExtents();
    Vector3 point = ray.getOrigin();
    Vector3 dir = ray.getDirection();

    // first, does the ray start from inside the terrain extents?
    if (!box.contains(point))
    {
      // not inside the box, so let's see if we are actually
      // colliding with it
      pair<bool, Real> res = ray.intersects(box);
      if (!res.first)
        return make_pair(false, Vector3::ZERO);
      // update point to the collision position
      point = ray.getPoint(res.second);
    }

    // now move along the ray until we intersect or leave the bounding box
    while (true)
    {
      // have we arived at or under the terrain height?
      // note that this approach means that ray queries from below won't work
      // correctly, but then again, that shouldn't be a usual case...
      float height = getHeightAt(point.x, point.z);
      if (point.y <= height)
      {
        point.y = height;
        return make_pair(true, point);
      }

      // move further...
      point += dir;

      // check if we are still inside the boundaries
      if (point.x < box.getMinimum().x || point.z < box.getMinimum().z
        || point.x > box.getMaximum().x || point.z > box.getMaximum().z)
        return make_pair(false, Vector3::ZERO);

    }
  }