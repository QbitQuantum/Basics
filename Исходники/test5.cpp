void calc()
{
  //std::cout << "M : " << std::endl << M.inverse() << std::endl;
  //          << "J : " << std::endl << J << std::endl << std::endl;
  Eigen::MatrixXd M_inv = M.inverse();
  Eigen::MatrixXd Jv = J.block(0, 0, 3, J.cols());
  Eigen::MatrixXd Lambda_inv = Jv * M_inv * Jv.transpose();
  Eigen::MatrixXd Lambda = Lambda_inv.inverse();
  Eigen::MatrixXd J_dyn_inv = M_inv * Jv.transpose() * Lambda;
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(15, 15);
  Eigen::MatrixXd N = I - J_dyn_inv * Jv;

  //std::cout << N.transpose() << std::endl << std::endl;
}