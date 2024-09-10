int	collideBoxSphere(CollisionObject* o1, CollisionObject* o2,
                     const Eigen::Vector3d& size0, const Eigen::Isometry3d& T0,
                     const double& r1, const Eigen::Isometry3d& T1,
                     CollisionResult& result)
{
  Eigen::Vector3d halfSize = 0.5 * size0;
  bool inside_box = true;

  // clipping a center of the sphere to a boundary of the box
  //Vec3 c0(&T0[9]);
  Eigen::Vector3d c0 = T1.translation();
  Eigen::Vector3d p = T0.inverse() * c0;

  if (p[0] < -halfSize[0]) { p[0] = -halfSize[0]; inside_box = false; }
  if (p[0] >  halfSize[0]) { p[0] =  halfSize[0]; inside_box = false; }

  if (p[1] < -halfSize[1]) { p[1] = -halfSize[1]; inside_box = false; }
  if (p[1] >  halfSize[1]) { p[1] =  halfSize[1]; inside_box = false; }

  if (p[2] < -halfSize[2]) { p[2] = -halfSize[2]; inside_box = false; }
  if (p[2] >  halfSize[2]) { p[2] =  halfSize[2]; inside_box = false; }


  Eigen::Vector3d normal(0.0, 0.0, 0.0);
  double penetration;

  if ( inside_box )
  {
    // find nearest side from the sphere center
    double min = halfSize[0] - std::abs(p[0]);
    double tmin = halfSize[1] - std::abs(p[1]);
    int idx = 0;

    if ( tmin < min )
    {
      min = tmin;
      idx = 1;
    }
    tmin = halfSize[2] - std::abs(p[2]);
    if ( tmin < min )
    {
      min = tmin;
      idx = 2;
    }

    //normal[idx] = (p[idx] > 0.0 ? 1.0 : -1.0);
    normal[idx] = (p[idx] > 0.0 ? -1.0 : 1.0);
    normal = T0.linear() * normal;
    penetration = min + r1;

    Contact contact;
    contact.collisionObject1 = o1;
    contact.collisionObject2 = o2;
    contact.point = c0;
    contact.normal = normal;
    contact.penetrationDepth = penetration;
    result.addContact(contact);
    return 1;
  }

  Eigen::Vector3d contactpt = T0 * p;
  //normal = c0 - contactpt;
  normal = contactpt - c0;
  double mag = normal.norm();
  penetration = r1 - mag;

  if (penetration < 0.0)
  {
    return 0;
  }

  if (mag > DART_COLLISION_EPS)
  {
    normal *= (1.0/mag);

    Contact contact;
    contact.collisionObject1 = o1;
    contact.collisionObject2 = o2;
    contact.point = contactpt;
    contact.normal = normal;
    contact.penetrationDepth = penetration;
    result.addContact(contact);
  }
  else
  {
    double min = halfSize[0] - std::abs(p[0]);
    double tmin = halfSize[1] - std::abs(p[1]);
    int idx = 0;

    if ( tmin < min )
    {
      min = tmin;
      idx = 1;
    }
    tmin = halfSize[2] - std::abs(p[2]);
    if ( tmin < min )
    {
      min = tmin;
      idx = 2;
    }
    normal.setZero();
    //normal[idx] = (p[idx] > 0.0 ? 1.0 : -1.0);
    normal[idx] = (p[idx] > 0.0 ? -1.0 : 1.0);
    normal = T0.linear() * normal;

    Contact contact;
    contact.collisionObject1 = o1;
    contact.collisionObject2 = o2;
    contact.point = contactpt;
    contact.normal = normal;
    contact.penetrationDepth = penetration;
    result.addContact(contact);
  }
  return 1;
}