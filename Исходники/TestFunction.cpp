 void updateHessian() const
 {
   MatrixXd& H = *IFunction<PARTIAL_XX>::_val[0];
   VectorXd q = static_cast<VectorXd>(x).array().inverse();
   H = (x.getSize()*q.array()*q.array()).matrix().asDiagonal();
   H -= q*q.transpose();    //Can be optimized by taking into account the symmetry of H and qq'
   H *= -getValue(0)/(x.getSize()*x.getSize());
 }