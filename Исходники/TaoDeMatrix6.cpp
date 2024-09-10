// X = [ R 0; dxR R ]
// L = X M = X [M00 M01; M10 M11]
//   = [ R M00  R M01; dx R M00 + R M10   dx R M01 + R M11]
// L00 = R M00
// L01 = R M01
// L10 = R M10 + dx L00
// L11 = R M11 + dx L01
void deMatrix6::xform(const deTransform& t, const deMatrix6& m)
{
  deMatrix3 tmpM;

  _mat3[0].multiply(t.rotation(), m._mat3[0]);

  _mat3[1].multiply(t.rotation(), m._mat3[1]);

  _mat3[2].multiply(t.rotation(), m._mat3[2]);
  tmpM.crossMultiply(t.translation(), _mat3[0]);
  _mat3[2] += tmpM;

  _mat3[3].multiply(t.rotation(), m._mat3[3]);
  tmpM.crossMultiply(t.translation(), _mat3[1]);
  _mat3[3] += tmpM;
}