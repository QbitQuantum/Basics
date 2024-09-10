T my_matrixfun(
       Eigen::Matrix<T,Eigen::Dynamic,1> const &a,
       Eigen::Matrix<T,Eigen::Dynamic,1> const &b){
   Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> m(a.size(),a.size());
   m.setZero();
   m.diagonal() = a;
   return (b.transpose() * m * b)(0,0);
}