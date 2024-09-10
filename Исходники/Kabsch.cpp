void TestFind3DAffineTransform(){

  // Create datasets with known transform
  Eigen::Matrix3Xd in(3, 100), out(3, 100);
  Eigen::Quaternion<double> Q(1, 3, 5, 2);
  Q.normalize();
  Eigen::Matrix3d R = Q.toRotationMatrix();
  double scale = 2.0;
  for (int row = 0; row < in.rows(); row++) {
    for (int col = 0; col < in.cols(); col++) {
      in(row, col) = log(2*row + 10.0)/sqrt(1.0*col + 4.0) + sqrt(col*1.0)/(row + 1.0);
    }
  }
  Eigen::Vector3d S;
  S << -5, 6, -27;
  for (int col = 0; col < in.cols(); col++)
    out.col(col) = scale*R*in.col(col) + S;

  Eigen::Affine3d A = Find3DAffineTransform(in, out);

  // See if we got the transform we expected
  if ( (scale*R-A.linear()).cwiseAbs().maxCoeff() > 1e-13 ||
       (S-A.translation()).cwiseAbs().maxCoeff() > 1e-13)
    throw "Could not determine the affine transform accurately enough";
}