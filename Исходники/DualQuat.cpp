DualScalar DualQuat::MagnitudeSquared() const {
  float a = 0;
  float b = 0;

  DualQuat q;
  q = *this;
  q = q.Conjugate();
  
  DualQuat p;
  p = (*this) * q;
  
  a = p._A.LengthSquared();
  b = p._B.LengthSquared();

  DualScalar d( a, b );
  return d;
}