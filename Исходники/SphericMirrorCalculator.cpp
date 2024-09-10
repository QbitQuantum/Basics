bool SphericMirrorCalculator::transform(const Vec3f &v,
										float &xb,float &yb) const {
  const Vec3f S = DomeCenter + (v * (DomeRadius/v.length()));
  const Vec3f SmP = S - P;
  const float P_SmP = P.dot(SmP);
  const bool rval = ( (PP-1.0)*SmP.dot(SmP) > P_SmP*P_SmP );
  
  const float lS = S.length();
  const Vec3f s(S/lS);
  float t_min = 0;
  float t_max = 1;
  Vec3f Q;
    // more iterations would be more accurate,
    // but I keep this number of iterations for exact zenith_y compatibility:
  for (int i=0;i<10;i++) {
	const float t = 0.5 * (t_min+t_max);
    Q = p*t + s*(1.0-t);
    Q.normalize();
	Vec3f Qp = P-Q;
    Qp.normalize();
	Vec3f Qs = S-Q;
    Qs.normalize();
    if ( (Qp-Qs).dot(Q) > 0.0 ) {
      t_max = t;
    } else {
      t_min = t;
    }
  }
  Vec3f x = Q-P;

    // rotate
  const float zb =
    alphaDeltaPhi[1]*x[0] + alphaDeltaPhi[4]*x[1] + alphaDeltaPhi[7]*x[2];
  xb = (horzZoomFactor/zb) *
   (alphaDeltaPhi[0]*x[0] + alphaDeltaPhi[3]*x[1] + alphaDeltaPhi[6]*x[2]);
  yb = (vertZoomFactor/zb) *
   (alphaDeltaPhi[2]*x[0] + alphaDeltaPhi[5]*x[1] + alphaDeltaPhi[8]*x[2]);

  return rval;
}