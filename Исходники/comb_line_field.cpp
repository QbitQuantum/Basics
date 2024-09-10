 // returns the 180 deg rotation of a (around n) most similar to target b
 // a and b should be in the same plane orthogonal to N
 static inline Eigen::Matrix<typename DerivedV::Scalar, 3, 1> K_PI_line(const Eigen::Matrix<typename DerivedV::Scalar, 3, 1>& a,
                                                                        const Eigen::Matrix<typename DerivedV::Scalar, 3, 1>& b)
 {
     typename DerivedV::Scalar scorea = a.dot(b);
     if (scorea<0)
         return -a;
     else
         return a;
 }