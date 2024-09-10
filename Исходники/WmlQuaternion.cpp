Quaternion<Real>
Quaternion<Real>::GetIntermediate(const Quaternion& rkQ0, const Quaternion& rkQ1, const Quaternion& rkQ2)
{
  // assert:  Q0, Q1, Q2 all unit-length
  Quaternion<Real> kQ1Inv = rkQ1.Conjugate();
  Quaternion<Real> kP0 = kQ1Inv* rkQ0;
  Quaternion<Real> kP2 = kQ1Inv* rkQ2;
  Quaternion<Real> kArg = -((Real) 0.25) * (kP0.Log() + kP2.Log());
  Quaternion<Real> kA = rkQ1* kArg.Exp();
  return kA;
}