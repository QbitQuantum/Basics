bool OgreMesh::intersectTri(const Ogre::Ray &ray, IntersectResult &rtn, Triangle*itr, bool isplane) {
    std::pair<bool, Real> hit = isplane
      ? Ogre::Math::intersects(ray, Ogre::Plane(itr->v1.coord, itr->v2.coord,itr->v3.coord))
      : Ogre::Math::intersects(ray, itr->v1.coord, itr->v2.coord,itr->v3.coord, true, false);
    rtn.u = 0;
    rtn.v = 0;
    if (hit.first && hit.second < rtn.distance) {
      rtn.intersected = hit.first;
      rtn.distance = hit.second;
      Ogre::Vector3 nml=(itr->v1.coord-itr->v2.coord).
              crossProduct(itr->v3.coord-itr->v2.coord);
      rtn.normal.x=nml.x;
      rtn.normal.y=nml.y;
      rtn.normal.z=nml.z;
      rtn.tri = *itr;
      Ogre::Vector3 intersect = ray.getPoint(hit.second) - rtn.tri.v2.coord;
      Ogre::Vector3 aVec = (rtn.tri.v1.coord - rtn.tri.v2.coord);
      Ogre::Vector3 bVec = (rtn.tri.v3.coord - rtn.tri.v2.coord);
      if (aVec.length() > 1.0e-10 && bVec.length() > 1.0e-10) {
        rtn.u = rtn.tri.v2.u + (rtn.tri.v1.u - rtn.tri.v2.u)*cos(aVec.angleBetween(intersect).valueRadians())*intersect.length()/aVec.length();
        rtn.v = rtn.tri.v2.v + (rtn.tri.v3.v - rtn.tri.v2.v)*cos(bVec.angleBetween(intersect).valueRadians())*intersect.length()/bVec.length();
      }
    }
    return rtn.intersected;
}