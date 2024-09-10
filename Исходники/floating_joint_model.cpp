void robot_model::FloatingJointModel::computeJointStateValues(const Eigen::Affine3d& transf, std::vector<double> &joint_values) const
{
  joint_values.resize(7);
  joint_values[0] = transf.translation().x();
  joint_values[1] = transf.translation().y();
  joint_values[2] = transf.translation().z();
  Eigen::Quaterniond q(transf.rotation());
  joint_values[3] = q.x();
  joint_values[4] = q.y();
  joint_values[5] = q.z();
  joint_values[6] = q.w();
}