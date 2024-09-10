 inline T determinant(const Eigen::Matrix<T, R, C>& m) {
   check_square("determinant", "m", m);
   return m.determinant();
 }