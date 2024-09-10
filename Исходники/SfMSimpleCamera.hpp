 SimpleCamera(
   const Mat3 & K = Mat3::Identity(),
   const Mat3 & R = Mat3::Identity(),
   const Vec3 & t = Vec3::Zero())
   : _K(K), _R(R), _t(t)
 {
   _C = -R.transpose() * t;
   P_From_KRt(_K, _R, _t, &_P);
 }