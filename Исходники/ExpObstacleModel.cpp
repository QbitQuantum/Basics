Vector2<> ExpObstacleModel::ExpObstacle::getLeftFoot() const
{
  Vector2<> result = center;
  result.normalize(type == GOALPOST ? goalPostRadius : feetRadius);
  result.rotateLeft();
  return center + result;
}