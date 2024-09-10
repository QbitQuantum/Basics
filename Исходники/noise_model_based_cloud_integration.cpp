void
NMBasedCloudIntegration<PointT>::collectInfo ()
{
  size_t total_point_count = 0;
  for(size_t i = 0; i < input_clouds_.size(); i++)
    total_point_count += (indices_.empty() || indices_[i].empty()) ? input_clouds_[i]->size() : indices_[i].size();
  VLOG(1) << "Allocating memory for point information of " << total_point_count << "points. ";
  big_cloud_info_.resize(total_point_count);


  std::vector<pcl::PointCloud<PointT> > input_clouds_aligned (input_clouds_.size());
  std::vector<pcl::PointCloud<pcl::Normal> > input_normals_aligned (input_clouds_.size());

#pragma omp parallel for schedule(dynamic)
  for(size_t i=0; i < input_clouds_.size(); i++)
  {
      pcl::transformPointCloud(*input_clouds_[i], input_clouds_aligned[i], transformations_to_global_[i]);
      transformNormals(*input_normals_[i], input_normals_aligned[i], transformations_to_global_[i]);
  }

  size_t point_count = 0;
  for(size_t i=0; i < input_clouds_.size(); i++)
  {
    const pcl::PointCloud<PointT> &cloud_aligned = input_clouds_aligned[i];
    const pcl::PointCloud<pcl::Normal> &normals_aligned = input_normals_aligned[i];

    size_t kept_new_pts = 0;
    if (indices_.empty() || indices_[i].empty())
    {
      for(size_t jj=0; jj<cloud_aligned.points.size(); jj++)
      {
        if ( !pcl::isFinite(cloud_aligned.points[jj]) || !pcl::isFinite(normals_aligned.points[jj]) )
          continue;

        PointInfo &pt = big_cloud_info_[point_count + kept_new_pts];
        pt.pt = cloud_aligned.points[jj];
        pt.normal = normals_aligned.points[jj];
        pt.sigma_lateral = pt_properties_[i][jj][0];
        pt.sigma_axial = pt_properties_[i][jj][1];
        pt.distance_to_depth_discontinuity = pt_properties_[i][jj][2];
        pt.pt_idx = jj;
        kept_new_pts++;
      }
    }
    else
    {
      for(int idx : indices_[i])
      {
        if ( !pcl::isFinite(cloud_aligned.points[idx]) || !pcl::isFinite(normals_aligned.points[idx]) )
           continue;

        PointInfo &pt = big_cloud_info_[point_count + kept_new_pts];
        pt.pt = cloud_aligned.points[idx];
        pt.normal = normals_aligned.points[ idx ];
        pt.sigma_lateral = pt_properties_[i][idx][0];
        pt.sigma_axial = pt_properties_[i][idx][1];
        pt.distance_to_depth_discontinuity = pt_properties_[i][idx][2];
        pt.pt_idx = idx;
        kept_new_pts++;
      }
    }

    // compute and store remaining information
#pragma omp parallel for schedule (dynamic) firstprivate(i, point_count, kept_new_pts)
    for(size_t jj=0; jj<kept_new_pts; jj++)
    {
      PointInfo &pt = big_cloud_info_ [point_count + jj];
      pt.origin = i;

      Eigen::Matrix3f sigma = Eigen::Matrix3f::Zero(), sigma_aligned = Eigen::Matrix3f::Zero();
      sigma(0,0) = pt.sigma_lateral;
      sigma(1,1) = pt.sigma_lateral;
      sigma(2,2) = pt.sigma_axial;

      const Eigen::Matrix4f &tf = transformations_to_global_[ i ];
      Eigen::Matrix3f rotation = tf.block<3,3>(0,0); // or inverse?
      sigma_aligned = rotation * sigma * rotation.transpose();
      double det = sigma_aligned.determinant();

//      if( std::isfinite(det) && det>0)
//          pt.probability = 1 / sqrt(2 * M_PI * det);
//      else
//          pt.probability = std::numeric_limits<float>::min();

      if( std::isfinite(det) && det>0)
          pt.weight = det;
      else
          pt.weight = std::numeric_limits<float>::max();
    }

    point_count += kept_new_pts;
  }

  big_cloud_info_.resize(point_count);
}