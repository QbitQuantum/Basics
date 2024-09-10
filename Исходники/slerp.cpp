void Slerp(Quaternion q1, Quaternion q2, Quaternion &qr , double lambda) 
{
  float dotproduct = q1.u.x * q2.u.x + q1.u.y * q2.u.y + q1.u.z * q2.u.z + q1.w * q2.w;
  float theta, st, sut, sout, coeff1, coeff2;

  // algorithm adapted from Shoemake's paper
  lambda=lambda/2.0;

  theta = (float) acos(dotproduct);
  if (theta<0.0) theta=-theta;
	
  st = (float) sin(theta);
  sut = (float) sin(lambda*theta);
  sout = (float) sin((1-lambda)*theta);
  coeff1 = sout/st;
  coeff2 = sut/st;

  qr.u.x = coeff1*q1.u.x + coeff2*q2.u.x;
  qr.u.y = coeff1*q1.u.y + coeff2*q2.u.y;
  qr.u.z = coeff1*q1.u.z + coeff2*q2.u.z;
  qr.w = coeff1*q1.w + coeff2*q2.w;

  qr.Normalize();
}