void LoadEstimator::getCrossMatrix(const Eigen::Vector3d& input_vector, Eigen::Matrix3d& crossed_matrix)
{
  crossed_matrix.setZero(3,3);

  crossed_matrix(0,1) = - input_vector(2);
  crossed_matrix(1,0) = input_vector(2);
  crossed_matrix(0,2) = input_vector(1);
  crossed_matrix(2,0) = - input_vector(1);
  crossed_matrix(1,2) = - input_vector(0);
  crossed_matrix(2,1) = input_vector(0);
}