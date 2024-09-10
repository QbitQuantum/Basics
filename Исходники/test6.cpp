void calc()
{
  Eigen::MatrixXd M_inv1 = M1.inverse();
  Eigen::MatrixXd M_inv2 = M2.inverse();
  Eigen::MatrixXd Jv1 = J1.block(0, 0, 3, J1.cols());
  Eigen::MatrixXd Jv2 = J2.block(0, 0, 3, J2.cols());
  Eigen::MatrixXd Lambda_inv1 = Jv1 * M_inv1 * Jv1.transpose();
  Eigen::MatrixXd Lambda_inv2 = Jv2 * M_inv2 * Jv2.transpose();
  Eigen::MatrixXd Lambda1 = Lambda_inv1.inverse();
  Eigen::MatrixXd Lambda2 = Lambda_inv2.inverse();
  Eigen::MatrixXd J_dyn_inv1 = M_inv1 * Jv1.transpose() * Lambda1;
  Eigen::MatrixXd J_dyn_inv2 = M_inv2 * Jv2.transpose() * Lambda2;
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(M_inv1.rows(), M_inv1.rows());
  Eigen::MatrixXd N1 = I - J_dyn_inv1 * Jv1;
  Eigen::MatrixXd N2 = I - J_dyn_inv2 * Jv2;

  //std::cout << N.transpose() << std::endl << std::endl;
}