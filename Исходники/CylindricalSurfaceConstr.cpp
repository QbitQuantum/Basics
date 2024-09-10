void CylindricalNVecConstr::impl_jacobian(jacobian_t& jac, const argument_t& x) const
{
  jac.reserve(jac_.dof());

  pgdata_->x(x);

  sva::PTransformd pos = surfaceFrame_*pgdata_->mbc().bodyPosW[bodyIndex_];
  Eigen::Vector3d vec = (targetFrame_.translation() - pos.translation());
  double dot = vec.dot(pos.rotation().row(2));
  double sign = std::copysign(1., dot);
  double vecNDot = sign*2.*vec.dot(pos.rotation().row(2));

  const Eigen::MatrixXd& jacVecNMat =
      jac_.vectorJacobian(pgdata_->mb(), pgdata_->mbc(),
                          surfaceFrame_.rotation().row(2).transpose());

  jacMat_.row(0).noalias() = vecNDot*vec.transpose()*jacVecNMat.block(3, 0, 3, jac_.dof());

  jac_.point(surfaceFrame_.translation());
  const Eigen::MatrixXd& jacMat = jac_.jacobian(pgdata_->mb(), pgdata_->mbc());
  jac_.point(Eigen::Vector3d::Zero());

  jacMat_.row(0).noalias() -= vecNDot*pos.rotation().row(2)*jacMat.block(3, 0, 3, jac_.dof());
  jacMat_.row(0).noalias() += (2.*vec.transpose())*jacMat.block(3, 0, 3, jac_.dof());

  fullJacobianSparse(pgdata_->mb(), jac_, jacMat_,
                     jac, {0, pgdata_->qParamsBegin()});
}