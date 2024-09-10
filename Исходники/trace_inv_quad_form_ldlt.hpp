 inline double
 trace_inv_quad_form_ldlt(const stan::math::LDLT_factor<double,R2,C2> &A,
                          const Eigen::Matrix<double,R3,C3> &B) {
   stan::math::validate_multiplicable(A,B,"trace_inv_quad_form_ldlt");
   
   return (B.transpose()*A._ldltP->solve(B)).trace();
 }