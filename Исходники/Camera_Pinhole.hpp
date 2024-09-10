 Pinhole_Intrinsic(
   unsigned int w = 0, unsigned int h = 0,
   double focal_length_pix = 0.0,
   double ppx = 0.0, double ppy = 0.0)
   :IntrinsicBase(w,h)
 {
   _K << focal_length_pix, 0., ppx, 0., focal_length_pix, ppy, 0., 0., 1.;
   _Kinv = _K.inverse();
 }