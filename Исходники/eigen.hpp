 static Eigen::Matrix<T, N, N> get(const Eigen::Matrix<T, N, N> &x) {
     return x.inverse();
 }