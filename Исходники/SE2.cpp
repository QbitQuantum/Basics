//==============================================================================
void SE2::logMap(const StateSpace::State* _in, Eigen::VectorXd& _tangent) const
{
  if (_tangent.rows() != 3)
    _tangent.resize(3);

  auto in = static_cast<const State*>(_in);

  Isometry2d transform = getIsometry(in);
  _tangent.head<2>() = transform.translation();
  Eigen::Rotation2Dd rotation = Eigen::Rotation2Dd::Identity();
  rotation.fromRotationMatrix(transform.rotation());
  _tangent[2] = rotation.angle();
}