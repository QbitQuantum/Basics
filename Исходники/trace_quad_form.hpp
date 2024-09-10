 inline double
 trace_quad_form(const Eigen::Matrix<double,RA,CA> &A,
                 const Eigen::Matrix<double,RB,CB> &B)
 {
   validate_square(A,"trace_quad_form");
   validate_multiplicable(A,B,"trace_quad_form");
   return (B.transpose()*A*B).trace();
 }