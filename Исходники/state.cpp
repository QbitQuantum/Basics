//==============================================================================
double State::getCoronalPelvisAngle() const
{
  Matrix3d comR = getCOMFrame().linear();
  Vector3d comY = comR.col(1);
  Vector3d pelvisZ = mPelvis->getTransform().linear().col(2);
  Vector3d projPelvisZ = (comR.transpose() * pelvisZ);
  projPelvisZ[0] = 0.0;
  projPelvisZ.normalize();
  double angle = _getAngleBetweenTwoVectors(projPelvisZ, comY);

  Vector3d cross = comY.cross(projPelvisZ);

  if (cross[0] > 0.0)
    return angle;
  else
    return -angle;
}