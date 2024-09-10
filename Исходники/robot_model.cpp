void RobotModel::setKinematicsToPlanningTransform(const KDL::Frame &f, std::string name)
{
  T_kinematics_to_planning_ = f;
  T_planning_to_kinematics_ = f.Inverse();
  planning_frame_ = name;
}