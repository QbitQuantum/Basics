 BrownPinholeCamera(
   double focal,
   double ppx,
   double ppy,
   const Mat3 & R = Mat3::Identity(),
   const Vec3 & t = Vec3::Zero(),
   double k1 = 0.0,
   double k2 = 0.0,
   double k3 = 0.0)
   : _R(R), _t(t), _f(focal), _ppx(ppx), _ppy(ppy),
   _k1(k1), _k2(k2), _k3(k3)
 {
   _C = -R.transpose() * t;
   _K << _f, 0, _ppx,
         0, _f, _ppy,
         0, 0,  1;
   P_From_KRt(_K, _R, _t, &_P);
 }