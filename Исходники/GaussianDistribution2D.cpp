void GaussianDistribution2D::getEigenVectorsAndEigenValues(Vector2<double>& eVec1, Vector2<double>& eVec2, 
                                                           double& eValue1, double& eValue2) const
{
  // Compute eigenvalues
  double cmTrace(covariance.trace());
  double cmDet(covariance.det());
  double sqrtExpression(sqrt(cmTrace*cmTrace - 4*cmDet));
  eValue1 = 0.5*(cmTrace + sqrtExpression);
  eValue2 = 0.5*(cmTrace - sqrtExpression);
  // Compute eigenvectors, general fomula:
  // | cm.c[0].x - eValue  cm.c[1].x          |  *  |x|   = |0|
  // | cm.c[0].y           cm.c[1].y - eValue |     |y|     |0|
  // First eigenvector (x set to 1):
  eVec1.x = 1.0;
  eVec1.y = -covariance.c[0].y / (covariance.c[1].y - eValue1);
  eVec1.normalize();
  // Second eigenvector (y set to 1):
  eVec2.x = -covariance.c[1].x / (covariance.c[0].x - eValue2);
  eVec2.y = 1.0;
  eVec2.normalize();
}