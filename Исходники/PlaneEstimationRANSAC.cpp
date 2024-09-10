/**
 * estimatePlaneLS
 * least squares estimation of a plan using points defined by indices
 */
void PlaneEstimationRANSAC::estimatePlaneLS(const std::vector<Eigen::Vector3f> &pts, const std::vector<int> &indices, Eigen::Vector3f &pt, Eigen::Vector3f &n)
{
  Eigen::Vector3f mean;
  EIGEN_ALIGN16 Eigen::Matrix3f cov;
  

  mean.setZero();

  for (unsigned j=0; j<indices.size(); j++)
    mean += pts[indices[j]];

  mean /= (float)indices.size();

  computeCovarianceMatrix(pts, indices, mean, cov);

  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> sv(cov);
  Eigen::Matrix3f eigen_vectors = sv.eigenvectors();

  n[0] = eigen_vectors(0,0);
  n[1] = eigen_vectors(1,0);
  n[2] = eigen_vectors(2,0);
}