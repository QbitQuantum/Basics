 /// af = aXb.act(bf)
 ForceTpl se3Action_impl(const SE3 & m) const
 {
   Vector3 Rf (static_cast<Vector3>( (m.rotation()) * linear_impl() ) );
   return ForceTpl(Rf,m.translation().cross(Rf)+m.rotation()*angular_impl());
 }