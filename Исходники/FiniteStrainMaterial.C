void
FiniteStrainMaterial::computeQpStrain(const RankTwoTensor & Fhat)
{
  //Cinv - I = A A^T - A - A^T;
  RankTwoTensor A; //A = I - Fhatinv
  A.addIa(1.0);
  A -= Fhat.inverse();
  RankTwoTensor Cinv_I = A*A.transpose() - A - A.transpose();

  //strain rate D from Taylor expansion, Chat = (-1/2(Chat^-1 - I) + 1/4*(Chat^-1 - I)^2 + ...
  _strain_increment[_qp] = -Cinv_I*0.5 + Cinv_I*Cinv_I*0.25;

  /*RankTwoTensor Chat = Fhat.transpose()*Fhat;
  RankTwoTensor A = Chat;
  A.addIa(-1.0);

  RankTwoTensor B = Chat*0.25;
  B.addIa(-0.75);
  _strain_increment[_qp] = -B*A;*/

  RankTwoTensor D = _strain_increment[_qp]/_t_step;
  _strain_rate[_qp] = D;

  //Calculate rotation R_incr
  RankTwoTensor invFhat(Fhat.inverse());

  std::vector<Real> a(3);
  a[0] = invFhat(1,2) - invFhat(2,1);
  a[1] = invFhat(2,0) - invFhat(0,2);
  a[2] = invFhat(0,1) - invFhat(1,0);
  Real q = (a[0]*a[0] + a[1]*a[1] + a[2]*a[2])/4.0;
  Real trFhatinv_1 = invFhat.trace() - 1.0;
  Real p = trFhatinv_1*trFhatinv_1/4.0;
  // Real y = 1.0/((q + p)*(q + p)*(q + p));

  /*Real C1 = std::sqrt(p * (1 + (p*(q+q+(q+p))) * (1-(q+p)) * y));
  Real C2 = 0.125 + q * 0.03125 * (p*p - 12*(p-1)) / (p*p);
  Real C3 = 0.5 * std::sqrt( (p*q*(3-q) + p*p*p + q*q)*y );
  */

  Real C1 = std::sqrt(p + 3.0*p*p*(1.0 - (p + q))/((p+q)*(p+q)) - 2.0*p*p*p*(1-(p+q))/((p+q)*(p+q)*(p+q))); //cos theta_a
  Real C2 = 0.0;
  if (q > 0.01)
    C2 = (1.0 - C1)/(4.0*q); // (1-cos theta_a)/4q
  else //alternate form for small q
    C2 = 0.125 + q*0.03125*(p*p - 12*(p-1))/(p*p) + q*q*(p - 2.0)*(p*p - 10.0*p + 32.0)/(p*p*p) + q*q*q*(1104.0 - 992.0*p + 376.0*p*p - 72*p*p*p + 5.0*p*p*p*p)/(512.0*p*p*p*p);

  Real C3 = 0.5*std::sqrt((p*q*(3.0 - q) + p*p*p + q*q)/((p + q)*(p + q)*(p + q))); //sin theta_a/(2 sqrt(q))

  //Calculate incremental rotation. Note that this value is the transpose of that from Rashid, 93, so we transpose it before storing
  RankTwoTensor R_incr;
  R_incr.addIa(C1);
  for (unsigned int i=0; i<3; ++i)
    for (unsigned int j = 0; j < 3; ++j)
      R_incr(i,j) += C2*a[i]*a[j];

  R_incr(0,1) += C3*a[2];
  R_incr(0,2) -= C3*a[1];
  R_incr(1,0) -= C3*a[2];
  R_incr(1,2) += C3*a[0];
  R_incr(2,0) += C3*a[1];
  R_incr(2,1) -= C3*a[0];
  _rotation_increment[_qp] = R_incr.transpose();
}