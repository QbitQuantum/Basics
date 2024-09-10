// another simple example: invert a matrix,
// returning a matrix
//
// [[Rcpp::export]]
Eigen::MatrixXd rcppeigen_matinv(const Eigen::MatrixXd & x) {
  Eigen::MatrixXd Xinv(x.inverse());
  return Xinv;
}