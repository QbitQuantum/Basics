Position2d PositionController::getStopLineReachedPose(const Pose2d& junction_start_pose) const
{
  Pose2d diff;
  PoseTraits<Pose2d>::fromPositionAndOrientationRPY(diff, -0.6, -0.23, 0.0);

  const Pose2d stop_pose = junction_start_pose * diff;

  ExtendedPose2d projection;
  double distance;
  std::size_t index;

  m_lateral_controller.calculateProjection(m_lateral_controller.getTrajectory(), stop_pose.translation(), projection, distance, index);

  return projection.getPosition();
}