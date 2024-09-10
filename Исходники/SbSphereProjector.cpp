/*!
  Check if \a point is on the frontside or the backside of the
  cylinder.
*/
SbBool
SbSphereProjector::isPointInFront(const SbVec3f & point) const
{
  const SbViewVolume & vv = this->getViewVolume();
  SbVec3f camdir;
  if (vv.getProjectionType() == SbViewVolume::PERSPECTIVE) {
    SbVec3f campos;
    this->worldToWorking.multVecMatrix(vv.getProjectionPoint(), campos);
    camdir = campos - this->sphere.getCenter();
  }
  else {
    this->worldToWorking.multDirMatrix( vv.zVector(), camdir);
  }
  SbVec3f ptdir = point - this->sphere.getCenter();
  return ptdir.dot(camdir) >= 0.0f;
}