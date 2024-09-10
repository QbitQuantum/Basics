static double multiplyVectorsImplementation(Eigen::Vector3d a,
                                            Eigen::Vector3d b,
                                            gtsam::OptionalJacobian<1,3> Ha,
                                            gtsam::OptionalJacobian<1,3> Hb) {
  if(Ha)
    *Ha = b.transpose();

  if(Hb)
    *Hb = a.transpose();

  return a.transpose() * b;
}