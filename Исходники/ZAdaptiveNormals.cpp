/**
 * ComputeNormal
 */
float ZAdaptiveNormals::computeNormal(const v4r::DataMatrix2D<Eigen::Vector3f> &cloud, std::vector<int> &indices, Eigen::Matrix3f &eigen_vectors)
{
  if (indices.size()<4)
    return NaN;

  Eigen::Vector3f mean;
  mean.setZero();
  for (unsigned j=0; j<indices.size(); j++)
    mean += cloud.data[indices[j]];
  mean /= (float)indices.size();

  Eigen::Matrix3f cov;
  computeCovarianceMatrix (cloud, indices, mean, cov);

  Eigen::Vector3f eigen_values;
  v4r::eigen33 (cov, eigen_vectors, eigen_values);
  float eigsum = eigen_values.sum();
  if (eigsum != 0)
    return fabs (eigen_values[0] / eigsum );
  
  return NaN;
}