bool XYOrbitViewController::intersectGroundPlane( Ogre::Ray mouse_ray, Ogre::Vector3 &intersection_3d )
{
  //convert rays into reference frame
  mouse_ray.setOrigin( target_scene_node_->convertWorldToLocalPosition( mouse_ray.getOrigin() ) );
  mouse_ray.setDirection( target_scene_node_->convertWorldToLocalOrientation( Ogre::Quaternion::IDENTITY ) * mouse_ray.getDirection() );

  Ogre::Plane ground_plane( Ogre::Vector3::UNIT_Z, 0 );

  std::pair<bool, Ogre::Real> intersection = mouse_ray.intersects(ground_plane);
  if (!intersection.first)
  {
    return false;
  }

  intersection_3d = mouse_ray.getPoint(intersection.second);
  return true;
}