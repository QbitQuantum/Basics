void AnchoredRectangleHandler::initRectangle(const Eigen::VectorXd& Fw,
    double lambda, const Eigen::VectorXd& z, Eigen::VectorXd& shapeParamshat,
    Eigen::VectorXd& FOhphat, Eigen::VectorXd &FOqhat) {

  //Get the points
  Eigen::Vector3d m1(z[0], z[1], 1);
  Eigen::Vector3d m2(z[2], z[3], 1);
  Eigen::Vector3d m3(z[4], z[5], 1);
  Eigen::Vector3d m4(z[6], z[7], 1);

  Eigen::Vector3d Ft(Fw[0], Fw[1], Fw[2]);
  Eigen::Quaterniond Fq(Fw[3], Fw[4], Fw[5], Fw[6]);

  //compute normals
  double c2 = (m1.cross(m3).transpose() * m4)[0]
      / (m2.cross(m3).transpose() * m4)[0];
  double c3 = (m1.cross(m3).transpose() * m2)[0]
      / (m4.cross(m3).transpose() * m2)[0];

  Eigen::Vector3d n2 = c2 * m2 - m1;
  Eigen::Vector3d n3 = c3 * m4 - m1;

  //Compute rotation matrix columns
  Eigen::Vector3d R1 = _K.inverse() * n2;
  R1 = R1 / R1.norm();

  Eigen::Vector3d R2 = _K.inverse() * n3;
  R2 = R2 / R2.norm();

  Eigen::Vector3d R3 = R1.cross(R2);

  //Compute rotation from camera to object
  Eigen::Matrix3d R;
  R << R1, R2, R3;
  Eigen::Quaterniond FOq_e(R);

  // and initialize the of the object with respect to the anchor frame
  FOqhat << FOq_e.w(), FOq_e.x(), FOq_e.y(), FOq_e.z();

  // now initialize lower left corner homogeneous point
  FOhphat << z[0], z[1], 1.0;
  FOhphat = _K.inverse() * FOhphat;
  FOhphat(2) = 1.0 / lambda; // 1/d distance of the plane parallel to the image plane on which features are initialized.

  //Compute frame transaltion
  Eigen::Matrix3d omega = _K.transpose().inverse() * _K.inverse();
  double ff = sqrt(
      (n2.transpose() * omega * n2)[0] / (n3.transpose() * omega * n3)[0]);

  //compute shape parameters
  Eigen::Vector3d X = _K * R1;
  Eigen::Vector3d Y = c2 * lambda * m2 - lambda * m1;

  double w = ((X.transpose() * X).inverse() * X.transpose() * Y)[0];

  //Write the results
  shapeParamshat << ff, w / lambda;

}