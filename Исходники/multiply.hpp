 inline double multiply(const Eigen::Matrix<double, 1, C1>& rv,
                        const Eigen::Matrix<double, R2, 1>& v) {
   stan::math::check_matching_sizes("multiply",
                                              "rv", rv,
                                              "v", v);
   if (rv.size() != v.size())
     throw std::domain_error("rv.size() != v.size()");
   return rv.dot(v);
 }