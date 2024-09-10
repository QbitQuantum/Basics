 inline double dot_product(const Eigen::Matrix<double, R1, C1>& v1, 
                           const Eigen::Matrix<double, R2, C2>& v2) {
   stan::math::check_vector("dot_product(%1%)",v1,"v1",(double*)0);
   stan::math::check_vector("dot_product(%1%)",v2,"v2",(double*)0);
   stan::math::check_matching_sizes("dot_product(%1%)",v1,"v1",
                                    v2,"v2",(double*)0);
   return v1.dot(v2);
 }