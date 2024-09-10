void constMatrix::gradient_add( const Eigen::VectorXd & X, const Eigen::VectorXd & iV)
{
  Eigen::VectorXd vtmp = Q * X;

  double xtQx =  vtmp.dot(iV.asDiagonal() * vtmp);
  dtau +=  (d - xtQx)/ tau;
  ddtau -=  (d + xtQx)/ pow(tau, 2);
}