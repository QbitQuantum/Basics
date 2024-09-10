template <typename PointInT, typename PointNT, typename PointLabelT, typename PointOutT> void
cob_3d_features::OrganizedCurvatureEstimation<PointInT,PointNT,PointLabelT,PointOutT>::computePointCurvatures (
  const NormalCloudIn &normals,
  const int index,
  const std::vector<int> &indices,
  const std::vector<float> &sqr_distances,
  float &pcx, float &pcy, float &pcz, float &pc1, float &pc2,
  int &label_out)
{
  Eigen::Vector3f n_idx(normals.points[index].normal);
  Eigen::Matrix3f M = Eigen::Matrix3f::Identity() - n_idx * n_idx.transpose(); // projection matrix

  std::vector<Eigen::Vector3f> normals_projected;
  normals_projected.reserve(n_points_);
  Eigen::Vector3f centroid = Eigen::Vector3f::Zero();
  Eigen::Vector3f p_idx = surface_->points[index].getVector3fMap();
  float angle = 0.0; // to discriminate convex and concave surface
  int prob_concave = 0, prob_convex = 0;
  for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); ++it)
  {
    PointNT const* n_i = &(normals.points[*it]);
    if ( pcl_isnan(n_i->normal[2]) ) continue;
    normals_projected.push_back( M * Eigen::Vector3f(n_i->normal) );
    centroid += normals_projected.back();
    if ( (surface_->points[*it].getVector3fMap() - p_idx).normalized().dot(n_idx) > 0.0) ++prob_concave;
    else ++prob_convex;
  }

  if (normals_projected.size() <=1) return;
  float num_p_inv = 1.0f / normals_projected.size();
  centroid *= num_p_inv;

  Eigen::Matrix3f cov = Eigen::Matrix3f::Zero();
  {
    std::vector<Eigen::Vector3f>::iterator n_it = normals_projected.begin();
    std::vector<float>::const_iterator d_it = sqr_distances.begin();
    for (; n_it != normals_projected.end(); ++n_it, ++d_it)
    {
      Eigen::Vector3f demean = *n_it - centroid;
      //cov += 1.0f / sqrt(*d_it) * demean * demean.transpose();
      cov += demean * demean.transpose();
    }
  }

  Eigen::Vector3f eigenvalues;
  Eigen::Matrix3f eigenvectors;
  pcl::eigen33(cov, eigenvectors, eigenvalues);
  pcx = eigenvectors (0,2);
  pcy = eigenvectors (1,2);
  pcz = eigenvectors (2,2);
  if (prob_concave < prob_convex) // if convex, make eigenvalues negative
    num_p_inv *= surface_->points[index].z * (-1);
  //num_p_inv *= 1.0 / (10.0*centroid.norm()) * surface_->points[index].z * (-1);
  else
    num_p_inv *= surface_->points[index].z;

  pc1 = eigenvalues (2) * num_p_inv;
  pc2 = eigenvalues (1) * num_p_inv;
  //normals_->points[index].curvature = curvatures_->points[index].pc1;
  if (std::abs(pc1) >= edge_curvature_threshold_ && label_out == 0)
    label_out = I_EDGE;
}