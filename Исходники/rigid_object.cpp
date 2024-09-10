void RigidObject::computeBoundingBox() {
  _bounding_box.resize(8 * 3);
  Eigen::Map<const Eigen::MatrixXf> vertices_f(getPositions().data(), 3,
                                               getNPositions());
  Eigen::MatrixXd vertices;
  vertices = vertices_f.cast<double>();

  // subtract vertices mean
  Eigen::Vector3d mean_vertices = vertices.rowwise().mean();
  vertices = vertices - mean_vertices.replicate(1, getNPositions());

  // compute eigenvector covariance matrix
  Eigen::EigenSolver<Eigen::MatrixXd> eigen_solver(vertices *
                                                   vertices.transpose());
  Eigen::MatrixXd real_eigenvectors = eigen_solver.eigenvectors().real();

  // rotate centered vertices with inverse eigenvector matrix
  vertices = real_eigenvectors.transpose() * vertices;

  // compute simple bounding box
  auto mn = vertices.rowwise().minCoeff();
  auto mx = vertices.rowwise().maxCoeff();
  Eigen::Matrix<double, 3, 8> bounding_box;
  bounding_box << mn(0), mn(0), mn(0), mn(0), mx(0), mx(0), mx(0), mx(0), mn(1),
      mn(1), mx(1), mx(1), mn(1), mn(1), mx(1), mx(1), mn(2), mx(2), mn(2),
      mx(2), mn(2), mx(2), mn(2), mx(2);

  // rotate and translate bounding box back to original position
  Eigen::Matrix3d rot_back = real_eigenvectors;
  Eigen::Translation<double, 3> tra_back(mean_vertices);
  Eigen::Transform<double, 3, Eigen::Affine> t = tra_back * rot_back;
  bounding_box = t * bounding_box;

  // convert to float
  Eigen::Map<Eigen::MatrixXf> bounding_box_f(_bounding_box.data(), 3, 8);

  bounding_box_f = bounding_box.cast<float>();
}