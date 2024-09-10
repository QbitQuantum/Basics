void FixedAxisOneDoFJoint::motionSubspaceDotTimesV(double* const q, double* const v,
    Vector6d& motion_subspace_dot_times_v,
    typename Gradient<Vector6d, Eigen::Dynamic>::type* dmotion_subspace_dot_times_vdq,
    typename Gradient<Vector6d, Eigen::Dynamic>::type* dmotion_subspace_dot_times_vdv) const
{
  motion_subspace_dot_times_v.setZero();

  if (dmotion_subspace_dot_times_vdq) {
    dmotion_subspace_dot_times_vdq->setZero(TWIST_SIZE, 1);
  }

  if (dmotion_subspace_dot_times_vdv) {
    dmotion_subspace_dot_times_vdv->setZero(TWIST_SIZE, 1);
  }
}