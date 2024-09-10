template<typename PointT, typename PointNT, typename PointLT> void
pcl::OrganizedMultiPlaneSegmentation<PointT, PointNT, PointLT>::segment (std::vector<ModelCoefficients>& model_coefficients, 
                                                                         std::vector<PointIndices>& inlier_indices,
                                                                         std::vector<Eigen::Vector4f, Eigen::aligned_allocator<Eigen::Vector4f> >& centroids,
                                                                         std::vector <Eigen::Matrix3f, Eigen::aligned_allocator<Eigen::Matrix3f> >& covariances,
                                                                         pcl::PointCloud<PointLT>& labels,
                                                                         std::vector<pcl::PointIndices>& label_indices)
{
  if (!initCompute ())
    return;

  // Check that we got the same number of points and normals
  if (static_cast<int> (normals_->points.size ()) != static_cast<int> (input_->points.size ()))
  {
    PCL_ERROR ("[pcl::%s::segment] Number of points in input cloud (%zu) and normal cloud (%zu) do not match!\n",
               getClassName ().c_str (), input_->points.size (),
               normals_->points.size ());
    return;
  }

  // Check that the cloud is organized
  if (!input_->isOrganized ())
  {
    PCL_ERROR ("[pcl::%s::segment] Organized point cloud is required for this plane extraction method!\n",
               getClassName ().c_str ());
    return;
  }

  // Calculate range part of planes' hessian normal form
  std::vector<float> plane_d (input_->points.size ());
  
  for (unsigned int i = 0; i < input_->size (); ++i)
    plane_d[i] = input_->points[i].getVector3fMap ().dot (normals_->points[i].getNormalVector3fMap ());
  
  // Make a comparator
  //PlaneCoefficientComparator<PointT,PointNT> plane_comparator (plane_d);
  compare_->setPlaneCoeffD (plane_d);
  compare_->setInputCloud (input_);
  compare_->setInputNormals (normals_);
  compare_->setAngularThreshold (static_cast<float> (angular_threshold_));
  compare_->setDistanceThreshold (static_cast<float> (distance_threshold_), true);

  // Set up the output
  OrganizedConnectedComponentSegmentation<PointT,pcl::Label> connected_component (compare_);
  connected_component.setInputCloud (input_);
  connected_component.segment (labels, label_indices);

  Eigen::Vector4f clust_centroid = Eigen::Vector4f::Zero ();
  Eigen::Vector4f vp = Eigen::Vector4f::Zero ();
  Eigen::Matrix3f clust_cov;
  pcl::ModelCoefficients model;
  model.values.resize (4);

  // Fit Planes to each cluster
  for (size_t i = 0; i < label_indices.size (); i++)
  {
    if (static_cast<unsigned> (label_indices[i].indices.size ()) > min_inliers_)
    {
      pcl::computeMeanAndCovarianceMatrix (*input_, label_indices[i].indices, clust_cov, clust_centroid);
      Eigen::Vector4f plane_params;
      
      EIGEN_ALIGN16 Eigen::Vector3f::Scalar eigen_value;
      EIGEN_ALIGN16 Eigen::Vector3f eigen_vector;
      pcl::eigen33 (clust_cov, eigen_value, eigen_vector);
      plane_params[0] = eigen_vector[0];
      plane_params[1] = eigen_vector[1];
      plane_params[2] = eigen_vector[2];
      plane_params[3] = 0;
      plane_params[3] = -1 * plane_params.dot (clust_centroid);

      vp -= clust_centroid;
      float cos_theta = vp.dot (plane_params);
      if (cos_theta < 0)
      {
        plane_params *= -1;
        plane_params[3] = 0;
        plane_params[3] = -1 * plane_params.dot (clust_centroid);
      }
      
      // Compute the curvature surface change
      float curvature;
      float eig_sum = clust_cov.coeff (0) + clust_cov.coeff (4) + clust_cov.coeff (8);
      if (eig_sum != 0)
        curvature = fabsf (eigen_value / eig_sum);
      else
        curvature = 0;

      if (curvature < maximum_curvature_)
      {
        model.values[0] = plane_params[0];
        model.values[1] = plane_params[1];
        model.values[2] = plane_params[2];
        model.values[3] = plane_params[3];
        model_coefficients.push_back (model);
        inlier_indices.push_back (label_indices[i]);
        centroids.push_back (clust_centroid);
        covariances.push_back (clust_cov);
      }
    }
  }
  deinitCompute ();
}