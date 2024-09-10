template<typename QuatType> void check_slerp(const QuatType& q0, const QuatType& q1)
{
  using std::abs;
  typedef typename QuatType::Scalar Scalar;
  typedef AngleAxis<Scalar> AA;

  Scalar largeEps = test_precision<Scalar>();

  Scalar theta_tot = AA(q1*q0.inverse()).angle();
  if(theta_tot>EIGEN_PI)
    theta_tot = Scalar(2.*EIGEN_PI)-theta_tot;
  for(Scalar t=0; t<=Scalar(1.001); t+=Scalar(0.1))
  {
    QuatType q = q0.slerp(t,q1);
    Scalar theta = AA(q*q0.inverse()).angle();
    VERIFY(abs(q.norm() - 1) < largeEps);
    if(theta_tot==0)  VERIFY(theta_tot==0);
    else              VERIFY(abs(theta - t * theta_tot) < largeEps);
  }
}