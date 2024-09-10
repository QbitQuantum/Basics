LIPStateEstimator::EstimatedState LIPStateEstimator::convertToOtherFoot(const EstimatedState& state) const
{
  EstimatedState otherState(state);
  otherState.supportFoot = state.supportFoot == SupportFoot::left ? SupportFoot::right : SupportFoot::left;
  otherState.origin.y() *= -1.f;

  const Pose3f& soleToTorso = state.supportFoot == SupportFoot::left ? theRobotModel.soleLeft : theRobotModel.soleRight;
  const Pose3f& otherSoleToTorso = state.supportFoot == SupportFoot::left ? theRobotModel.soleRight : theRobotModel.soleLeft;
  const Pose3f originToTorso = soleToTorso + Vector3f(state.origin.x(), state.origin.y(), 0.f);
  const Pose3f otherOriginToTorso = otherSoleToTorso + Vector3f(otherState.origin.x(), otherState.origin.y(), 0.f);

  //const Quaternionf& torsoToWorld = theInertiaData.orientation;
  //Pose3f oritinToOtherOrigin = Pose3f(torsoToWorld) * otherOriginToTorso.rotation * otherOriginToTorso.inverse() * originToTorso * originToTorso.rotation.inverse() *= torsoToWorld.inverse();

  const Pose3f oritinToOtherOrigin = otherOriginToTorso.inverse() * originToTorso;

  otherState.com.position = (oritinToOtherOrigin * Vector3f(state.com.position.x(), state.com.position.y(), 0.f)).head<2>();
  otherState.com.velocity = (oritinToOtherOrigin.rotation * Vector3f(state.com.velocity.x(), state.com.velocity.y(), 0.f)).head<2>();
  otherState.zmp = (oritinToOtherOrigin * Vector3f(state.zmp.x(), state.zmp.y(), 0.f)).head<2>();
  return otherState;
}