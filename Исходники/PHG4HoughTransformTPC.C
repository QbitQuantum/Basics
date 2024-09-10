static void convertHelixCovarianceToEuclideanCovariance( float B, float phi, float d, float kappa, float z0, float dzdl, Eigen::Matrix<float,5,5> const& input, Eigen::Matrix<float,6,6>& output )
{
  Matrix<float,6,5> J = Matrix<float,6,5>::Zero(6,5);
  // phi,d,nu,z0,dzdl
  // -->
  // x,y,z,px,py,pz
  float nu = sqrt(kappa);
  float dk_dnu = 2*nu;

  float cosphi = cos(phi);
  float sinphi = sin(phi);

  J( 0, 0 ) = -sinphi*d;
  J( 0, 1 ) = cosphi;
  J( 1, 0 ) = d*cosphi;
  J( 1, 1 ) = sinphi;
  J( 2, 3 ) = 1;

  float pt = 0.003*B/kappa;
  float dpt_dk = -0.003*B/(kappa*kappa);

  J( 3, 0 ) = -cosphi*pt;
  J( 3, 2 ) = -sinphi*dpt_dk*dk_dnu;
  J( 4, 0 ) = -sinphi*pt;
  J( 4, 2 ) = cosphi*dpt_dk*dk_dnu;

  float alpha = 1./(1. - dzdl*dzdl);
  float alpha_half = pow( alpha, 0.5 );
  float alpha_3_half = alpha*alpha_half;

  J( 5, 2 ) = dpt_dk*dzdl*alpha_half*dk_dnu;
  J( 5, 4 ) = pt*( alpha_half + dzdl*dzdl*alpha_3_half )*dk_dnu;

  output = J*input*(J.transpose());
}