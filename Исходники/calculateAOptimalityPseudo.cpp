// [[Rcpp::export]]
double calculateAOptimalityPseudo(const Eigen::MatrixXd& currentDesign) {
  Eigen::MatrixXd XtX = currentDesign.transpose()*currentDesign;
  return(XtX.completeOrthogonalDecomposition().pseudoInverse().trace());
}