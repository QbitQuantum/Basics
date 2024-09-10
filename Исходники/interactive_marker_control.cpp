bool InteractiveMarkerControl::intersectSomeYzPlane( const Ogre::Ray& mouse_ray,
                                                     const Ogre::Vector3& point_on_plane,
                                                     const Ogre::Quaternion& plane_orientation,
                                                     Ogre::Vector3& intersection_3d,
                                                     Ogre::Vector2& intersection_2d,
                                                     float& ray_t )
{
  Ogre::Vector3 normal = plane_orientation * control_orientation_.xAxis();
  Ogre::Vector3 axis_1 = plane_orientation * control_orientation_.yAxis();
  Ogre::Vector3 axis_2 = plane_orientation * control_orientation_.zAxis();

  Ogre::Plane plane(normal, point_on_plane);

  Ogre::Vector2 origin_2d(point_on_plane.dotProduct(axis_1), point_on_plane.dotProduct(axis_2));

  std::pair<bool, Ogre::Real> intersection = mouse_ray.intersects(plane);
  if (intersection.first)
  {
    intersection_3d = mouse_ray.getPoint(intersection.second);
    intersection_2d = Ogre::Vector2(intersection_3d.dotProduct(axis_1), intersection_3d.dotProduct(axis_2));
    intersection_2d -= origin_2d;

    ray_t = intersection.second;
    return true;
  }

  ray_t = 0;
  return false;
}