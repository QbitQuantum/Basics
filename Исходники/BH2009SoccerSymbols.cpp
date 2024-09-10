Vector2<double> BH2009SoccerSymbols::computePosition()
{
  Vector2<double> ballPosition = ballModel.estimate.getPositionInFieldCoordinates(theInstance->robotPose);
  Vector2<double> temp = ballPosition - Vector2<double>(fieldDimensions.xPosOpponentGroundline, 0);
  if(sideLeft) temp.rotateLeft();
  else temp.rotateRight();
  temp.normalize(300);
  return (temp + ballPosition);
}