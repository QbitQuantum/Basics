 double GaussianDiagCov<ScalarType>::calculateValueWithoutWeights(const Eigen::Matrix<ScalarType, Eigen::Dynamic, 1>& dataVector)
 {
     assert(dataVector.size() == mean.size());
     Eigen::Matrix<ScalarType, Eigen::Dynamic, 1> dist = dataVector - mean;
     //Eigen::Matrix<ScalarType, Eigen::Dynamic, 1> dist2 = dist;
     return preFactorWithoutWeights * std::exp(-0.5 * (dist.transpose() * ldlt.solve(dist))(0));
 }