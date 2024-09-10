 void se3ActionInverse_impl(const SE3Tpl<S2,O2> & m, MotionDense<D2> & v) const
 {
   // Linear
   // TODO: use v.angular() as temporary variable
   Vector3 v3_tmp;
   AxisZ::alphaCross(m_theta_dot,m.translation(),v3_tmp);
   v3_tmp[0] += m_x_dot; v3_tmp[1] += m_y_dot;
   v.linear().noalias() = m.rotation().transpose() * v3_tmp;
   
   // Angular
   v.angular().noalias() = m.rotation().transpose().col(2) * m_theta_dot;
 }