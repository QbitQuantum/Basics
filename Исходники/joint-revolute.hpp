 void se3Action_impl(const SE3Tpl<S2,O2> & m, MotionDense<D2> & v) const
 {
   v.angular().noalias() = m.rotation().col(axis) * w;
   v.linear().noalias() = m.translation().cross(v.angular());
 }