  void computeCovarianceMatrix(PointCloudRGB cloud, std::vector<int> indices, Eigen::Vector4f centroid, Eigen::Matrix3f &covariance_matrix)
  {
    // ROS_INFO("Inside computeCovarianceMatrix() ");
    // Initialize to 0
    covariance_matrix.setZero ();
    
    if (indices.empty ())
      return;
  
    // If the data is dense, we don't need to check for NaN
    if (cloud.is_dense)
      {
	// For each point in the cloud
	for (size_t i = 0; i < indices.size (); ++i)
	  {
	    //Eigen::Vector4f ptx = cloud.points[indices[i]].getVector4fMap ();
	    ///std::cout << "Index : "<< i <<" : "<<ptx<<std::endl;
	    Eigen::Vector4f pt = cloud.points[indices[i]].getVector4fMap () - centroid;
	    
	    covariance_matrix (0, 0) += pt.x () * pt.x ();
	    covariance_matrix (0, 1) += pt.x () * pt.y ();
	    covariance_matrix (0, 2) += pt.x () * pt.z ();
	    covariance_matrix (1, 1) += pt.y () * pt.y ();
	    covariance_matrix (1, 2) += pt.y () * pt.z ();	
	    covariance_matrix (2, 2) += pt.z () * pt.z ();
	  }

      }
    // NaN or Inf values could exist => check for them
    else
      {
	//std::cout<<"Cloud is not dense "<<std::endl;
	// For each point in the cloud
	for (size_t i = 0; i < indices.size (); ++i)
	  {
	    // Check if the point is invalid
	    if (!pcl_isfinite (cloud.points[indices[i]].x) || 
		!pcl_isfinite (cloud.points[indices[i]].y) || 
		!pcl_isfinite (cloud.points[indices[i]].z))
	      continue;
	    
	    // Eigen::Vector4f ptx = cloud.points[indices[i]].getVector4fMap ();
	    // std::cout << "Index : "<< i <<" : "<<ptx<<std::endl;
	    Eigen::Vector4f pt = cloud.points[indices[i]].getVector4fMap () - centroid;
	    
	    covariance_matrix (0, 0) += pt.x () * pt.x ();
	    covariance_matrix (0, 1) += pt.x () * pt.y ();
	    covariance_matrix (0, 2) += pt.x () * pt.z ();
	    covariance_matrix (1, 1) += pt.y () * pt.y ();
	    covariance_matrix (1, 2) += pt.y () * pt.z ();	
	    covariance_matrix (2, 2) += pt.z () * pt.z ();
	    covariance_matrix (1, 1) += pt.y () * pt.y ();
	  }
      }
    covariance_matrix (1, 0) = covariance_matrix (0, 1);
    covariance_matrix (2, 0) = covariance_matrix (0, 2);
    covariance_matrix (2, 1) = covariance_matrix (1, 2);
    
    covariance_matrix /= indices.size();
  }