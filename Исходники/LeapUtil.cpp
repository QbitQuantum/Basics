void Camera::SetPOVLookAt( const Vector& vCameraPosition, const Vector& vTarget, Vector vUp )
{
  Vector vZBasis = (vCameraPosition - vTarget).normalized();

  // if the zero vector was passed try to preserve the current camera up as much as possible
  if ( vUp == Vector::zero() )
  {
    vUp = m_mtxPOV.yBasis;
  }
  else
  {
    vUp = vUp.normalized();
  }

  // if the z direction is parallel to the desired up direction
  // we need to pick another up.
  if ( IsNearZero(1.0f - fabs(vZBasis.dot(vUp))) )
  {
    // make the new up perpendicular to the plane of the new z axis and the old right direction.
    // it's a decent guess.
    vUp = vZBasis.cross( m_mtxPOV.xBasis ).normalized();
  }

  Vector vXBasis = vUp.cross(vZBasis).normalized();
  Vector vYBasis = vZBasis.cross( vXBasis ).normalized();

  m_mtxPOV.xBasis = vXBasis;
  m_mtxPOV.yBasis = vYBasis;
  m_mtxPOV.zBasis = vZBasis;
  m_mtxPOV.origin = vCameraPosition;

  updateOrbitDistance();
}