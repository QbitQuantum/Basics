 // returns the 90 deg rotation of a (around n) most similar to target b
 /// a and b should be in the same plane orthogonal to N
 static inline Eigen::Matrix<typename DerivedV::Scalar, 3, 1> K_PI_new(const Eigen::Matrix<typename DerivedV::Scalar, 3, 1>& a,
                                                                const Eigen::Matrix<typename DerivedV::Scalar, 3, 1>& b,
                                                                const Eigen::Matrix<typename DerivedV::Scalar, 3, 1>& n)
 {
   Eigen::Matrix<typename DerivedV::Scalar, 3, 1> c = (a.cross(n)).normalized();
   typename DerivedV::Scalar scorea = a.dot(b);
   typename DerivedV::Scalar scorec = c.dot(b);
   if (fabs(scorea)>=fabs(scorec))
     return a*Sign(scorea);
   else
     return c*Sign(scorec);
 }