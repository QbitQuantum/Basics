  double
  radiusAndOriginFromCloud(pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr in_cloud ,
                  std::vector<int>& indices,
                  Eigen::Vector3f& origin,
                  const Eigen::Vector3f& sym_axis)
  {
    //  Transform into cylinder coordinate frame
    Eigen::Affine3f t;
    pcl::getTransformationFromTwoUnitVectorsAndOrigin(sym_axis.unitOrthogonal(), sym_axis, origin, t);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pc_trans( new pcl::PointCloud<pcl::PointXYZRGB>() );
    pcl::transformPointCloud(*in_cloud, indices, *pc_trans, t);

    // Inliers of circle model
    pcl::PointIndices inliers;
    // Coefficients of circle model
    pcl::ModelCoefficients coeff;
    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZRGB> seg;
    // Optimize coefficients
    seg.setOptimizeCoefficients (true);
    // Set type of method
    //seg.setMethodType (pcl::SAC_MLESAC);
    seg.setMethodType (pcl::SAC_RANSAC);
    // Set number of maximum iterations
    seg.setMaxIterations (10);
    // Set type of model
    seg.setModelType (pcl::SACMODEL_CIRCLE2D);
    // Set threshold of model
    seg.setDistanceThreshold (0.010);
    // Give as input the filtered point cloud
    seg.setInputCloud (pc_trans/*in_cloud*/);
    //boost::shared_ptr<std::vector<int> > indices_ptr(&indices);
    //seg.setIndices(indices_ptr);
    // Call the segmenting method
    seg.segment(inliers, coeff);


    // origin in cylinder coordinates
    Eigen::Vector3f l_origin;
    l_origin << coeff.values[0],coeff.values[1],0;
    origin = t.inverse() * l_origin;

    return coeff.values[2];
  }