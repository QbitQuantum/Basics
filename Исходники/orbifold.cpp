Vector3d OrbifoldData::collapseX632(const Vector3d& pt, Vector3d& out_dir) const {
  const double SQRT_3_OVER_2 = 0.8660254037844386;
  const double SQRT_3_OVER_4 = 0.8660254037844386 * 0.5;
  const double SQRT_3_OVER_3 = 0.5773502691896257;
  const double SQRT_3_OVER_6 = 0.5773502691896257 * 0.5;
  const double ONE_THIRD = (1.0/3.0);
  const double ONE_SIXTH = (1.0/6.0);

  const Vector2d o = -direction_info[0].base;
  const Vector2d e = Vector2d(pt.x(), pt.z()) - direction_info[0].base;
  Vector2d d = (e-o);
  d.normalize();

  // Homogeneous
  const StaticDirectionInfo sdi1 = { Vector2d{-0.5, SQRT_3_OVER_2},
                                     Vector2d{SQRT_3_OVER_2, 0.5},
                                     { 1, 1, 1 } };
  const StaticDirectionInfo sdi2 = { Vector2d{0.5, SQRT_3_OVER_2},
                                     Vector2d{SQRT_3_OVER_2, -0.5},
                                     { 1, 1, 1 } };
  const StaticDirectionInfo sdi3 = { Vector2d{-1, 0},
                                     Vector2d{0, 1},
                                     { 1, 1, 1 } };
  // Heterogeneous
  const StaticDirectionInfo sdi4 = { Vector2d{0, 1},
                                     Vector2d{1, 0},
                                     { 2, 0, 2 } };
  const StaticDirectionInfo sdi5 = { Vector2d{-SQRT_3_OVER_2, 0.5},
                                     Vector2d{0.5, SQRT_3_OVER_2},
                                     { 2, 0, 2 } };
  const StaticDirectionInfo sdi6 = { Vector2d{SQRT_3_OVER_2, 0.5},
                                     Vector2d{0.5, -SQRT_3_OVER_2},
                                     { 2, 0, 2 } };


  // These values will be negative if the path from the origin to the point is going
  // opposite to the normal of the mirror
  const double sign1 = sign<double>(dot(d, sdi1.o));
  const double sign2 = sign<double>(dot(d, sdi2.o));
  const double sign3 = sign<double>(dot(d, sdi3.o));
  const double sign4 = sign<double>(dot(d, sdi4.o));
  const double sign5 = sign<double>(dot(d, sdi5.o));
  const double sign6 = sign<double>(dot(d, sdi6.o));

  Vector2d p(0, 0);

  const unsigned n1 = countMirrorsHomogeneous(o, e, d, sdi1, direction_info[1]);
  p += static_cast<double>(n1)*sign1*ONE_THIRD * sdi1.o;

  const unsigned n2 = countMirrorsHomogeneous(o, e, d, sdi2, direction_info[1]);
  p += static_cast<double>(n2)*sign2*ONE_THIRD * sdi2.o;

  const unsigned n3 = countMirrorsHomogeneous(o, e, d, sdi3, direction_info[1]);
  p += static_cast<double>(n3)*sign3*ONE_THIRD * sdi3.o;


  unsigned mc1[3] = {0, 0, 0};
  countMirrorsHeterogeneous(o, e, d, sdi4, direction_info[0], mc1);
  p += sign4*(mc1[0]*SQRT_3_OVER_3 + mc1[1]*ONE_THIRD + mc1[2]*ONE_THIRD) * sdi4.o;
  const unsigned n4 = mc1[0] + mc1[1] + mc1[2];

  unsigned mc2[3] = {0, 0, 0};
  countMirrorsHeterogeneous(o, e, d, sdi5, direction_info[0], mc2);
  p += sign5*(mc2[0]*SQRT_3_OVER_3 + mc2[1]*ONE_THIRD + mc2[2]*ONE_THIRD) * sdi5.o;
  const unsigned n5 = mc2[0] + mc2[1] + mc2[2];

  unsigned mc3[3] = {0, 0, 0};
  countMirrorsHeterogeneous(o, e, d, sdi6, direction_info[0], mc3);
  p += sign6*(mc3[0]*SQRT_3_OVER_3 + mc3[1]*ONE_THIRD + mc3[2]*ONE_THIRD) * sdi6.o;
  const unsigned n6 = mc3[0] + mc3[1] + mc3[2];

  p *= scale.x();

  Vector3d ret = pt;
  ret.x() -= p.x();
  ret.z() -=  p.y();

  if(n1 % 2 != 0) {
    reflect(sdi1.o, ret, out_dir);
  }
  if(n2 % 2 != 0) {
    reflect(sdi2.o, ret, out_dir);
  }
  if(n3 % 2 != 0) {
    reflect(sdi3.o, ret, out_dir);
  }
  if(n4 % 2 != 0) {
    reflect(sdi4.o, ret, out_dir);
  }
  if(n5 % 2 != 0) {
    reflect(sdi5.o, ret, out_dir);
  }
  if(n6 % 2 != 0) {
    reflect(sdi6.o, ret, out_dir);
  }
  return ret;
}