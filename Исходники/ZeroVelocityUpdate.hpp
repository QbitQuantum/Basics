 /** \brief Computes the Jacobian for the update step of the filter.
  *
  *  @param F     - Jacobian for the update step of the filter.
  *  @param state - Filter state.
  *  @param meas  - Not used.
  *  @param dt    - Not used.
  */
 void jacInput(mtJacInput& F, const mtState& state, const mtMeas& meas, double dt = 0.0) const{
   F.setZero();
   F.template block<3,3>(mtInnovation::template getId<mtInnovation::_vel>(),mtState::template getId<mtState::_vel>()) = Eigen::Matrix3d::Identity();
 }