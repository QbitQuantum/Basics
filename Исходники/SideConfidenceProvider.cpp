bool SideConfidenceProvider::ballModelCanBeUsed(const BallModel& ballModel, const Pose2f& robotPose) const
{
  // Is the ball model still "fresh"?
  if(theFrameInfo.getTimeSince(ballModel.timeWhenLastSeen) > maxBallAge)
    return false;
  // We do not want to consider fast rolling balls for the SideConfidence:
  if(ballModel.estimate.velocity.norm() > maxBallVelocity)
    return false;
  // Close to the field center, the ball information does not help:
  const Vector2f globalPos = robotPose * ballModel.estimate.position;
  if(globalPos.norm() < centerBanZoneRadius)
    return false;
  // As the perception of the new ball might be unreliable, we only consider stuff away from lines:
  if(ballIsCloseToPenaltyMarkOrLine(globalPos))
    return false;
  return true;
}