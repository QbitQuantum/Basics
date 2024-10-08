void
v4r::MultiPlaneSegmentation<PointT>::segment(bool force_unorganized)
{
  models_.clear();

  if(input_->isOrganized() && !force_unorganized)
  {
    pcl::PointCloud<pcl::Normal>::Ptr normal_cloud (new pcl::PointCloud<pcl::Normal>);
    if(!normals_set_)
    {
        pcl::IntegralImageNormalEstimation<PointT, pcl::Normal> ne;
        ne.setNormalEstimationMethod (ne.COVARIANCE_MATRIX);
        ne.setMaxDepthChangeFactor (0.02f);
        ne.setNormalSmoothingSize (20.0f);
        ne.setBorderPolicy (pcl::IntegralImageNormalEstimation<PointT, pcl::Normal>::BORDER_POLICY_IGNORE);
        ne.setInputCloud (input_);
        ne.compute (*normal_cloud);
    }
    else
    {
        normal_cloud = normal_cloud_;
    }

    pcl::OrganizedMultiPlaneSegmentation<PointT, pcl::Normal, pcl::Label> mps;
    mps.setMinInliers (min_plane_inliers_);
    mps.setAngularThreshold (0.017453 * 2.f); // 2 degrees
    mps.setDistanceThreshold (0.01); // 1cm
    mps.setMaximumCurvature(0.002);
    mps.setInputNormals (normal_cloud);
    mps.setInputCloud (input_);

    std::vector<pcl::PlanarRegion<PointT>, Eigen::aligned_allocator<pcl::PlanarRegion<PointT> > > regions;
    std::vector<pcl::ModelCoefficients> model_coefficients;
    std::vector<pcl::PointIndices> inlier_indices;
    pcl::PointCloud<pcl::Label>::Ptr labels (new pcl::PointCloud<pcl::Label>);
    std::vector<pcl::PointIndices> label_indices;
    std::vector<pcl::PointIndices> boundary_indices;

    typename pcl::PlaneRefinementComparator<PointT, pcl::Normal, pcl::Label>::Ptr ref_comp (
                                                                                             new pcl::PlaneRefinementComparator<PointT,
                                                                                                 pcl::Normal, pcl::Label> ());
    ref_comp->setDistanceThreshold (0.01f, false);
    ref_comp->setAngularThreshold (0.017453 * 2.f);
    mps.setRefinementComparator (ref_comp);
    mps.segmentAndRefine (regions, model_coefficients, inlier_indices, labels, label_indices, boundary_indices);
    //mps.segment (model_coefficients, inlier_indices);

    //std::cout << model_coefficients.size() << std::endl;

    if(merge_planes_)
    {
      //sort planes by size
      //check if the first plane can be merged against the others, if yes, define a new plane combining both and add it to the cue

      typedef boost::adjacency_matrix<boost::undirectedS, int> GraphPlane;
      GraphPlane mergeable_planes (model_coefficients.size ());
      for(size_t i=0; i < model_coefficients.size(); i++)
      {

        Eigen::Vector3f plane_i = Eigen::Vector3f (model_coefficients[i].values[0], model_coefficients[i].values[1],
                                                   model_coefficients[i].values[2]);

        plane_i.normalize();
        for(size_t j=(i+1); j < model_coefficients.size(); j++)
        {
          Eigen::Vector3f plane_j = Eigen::Vector3f (model_coefficients[j].values[0], model_coefficients[j].values[1],
                                                     model_coefficients[j].values[2]);

          plane_j.normalize();

          //std::cout << "dot product:" << plane_i.dot(plane_j) << " diff:" << std::abs(model_coefficients[i].values[3] - model_coefficients[j].values[3]) << std::endl;
          if(plane_i.dot(plane_j) > 0.95)
          {
            if(std::abs(model_coefficients[i].values[3] - model_coefficients[j].values[3]) < 0.015)
            {
              boost::add_edge (static_cast<int>(i), static_cast<int>(j), mergeable_planes);
            }
          }
        }
      }

      boost::vector_property_map<int> components (boost::num_vertices (mergeable_planes));
      int n_cc = static_cast<int> (boost::connected_components (mergeable_planes, &components[0]));

      std::vector<int> cc_sizes;
      std::vector< std::vector<int> > cc_to_model_coeff;
      cc_sizes.resize (n_cc, 0);
      cc_to_model_coeff.resize(n_cc);

      for (size_t i = 0; i < model_coefficients.size (); i++)
      {
        cc_sizes[components[i]]++;
        cc_to_model_coeff[components[i]].push_back(i);
      }

      std::vector<pcl::ModelCoefficients> new_model_coefficients;
      std::vector<pcl::PointIndices> new_inlier_indices;

      for(size_t i=0; i < cc_sizes.size(); i++)
      {
        if(cc_sizes[i] < 2)
        {
          new_model_coefficients.push_back(model_coefficients[cc_to_model_coeff[i][0]]);
          new_inlier_indices.push_back(inlier_indices[cc_to_model_coeff[i][0]]);
          continue;
        }

        //std::cout << "going to merge CC:" << cc_sizes[i] << std::endl;
        pcl::ModelCoefficients model_coeff;
        model_coeff.values.resize(4);

        for(size_t k=0; k < 4; k++)
          model_coeff.values[k] = 0.f;

        pcl::PointIndices merged_indices;
        for(size_t j=0; j < cc_to_model_coeff[i].size(); j++)
        {
          for(size_t k=0; k < 4; k++)
            model_coeff.values[k] += model_coefficients[cc_to_model_coeff[i][j]].values[k];

          merged_indices.indices.insert(merged_indices.indices.end(), inlier_indices[cc_to_model_coeff[i][j]].indices.begin(),
                                                                      inlier_indices[cc_to_model_coeff[i][j]].indices.end());
        }

        for(size_t k=0; k < 4; k++)
          model_coeff.values[k] /= static_cast<float>(cc_to_model_coeff[i].size());

        new_model_coefficients.push_back(model_coeff);
        new_inlier_indices.push_back(merged_indices);
      }

      model_coefficients = new_model_coefficients;
      inlier_indices = new_inlier_indices;
    }

    for(size_t i=0; i < model_coefficients.size(); i++)
    {
      PlaneModel<PointT> pm;
      pm.coefficients_ = model_coefficients[i];
      pm.cloud_ = input_;
      pm.inliers_ = inlier_indices[i];

      //recompute coefficients based on distance to camera and normal?
      Eigen::Vector4f centroid;
      pcl::compute3DCentroid(*pm.cloud_, pm.inliers_, centroid);
      Eigen::Vector3f c(centroid[0],centroid[1],centroid[2]);

      Eigen::MatrixXf M_w(inlier_indices[i].indices.size(), 3);

      float sum_w = 0.f;
      for(size_t k=0; k < inlier_indices[i].indices.size(); k++)
      {
          const int &idx = inlier_indices[i].indices[k];
          float d_c = (pm.cloud_->points[idx].getVector3fMap()).norm();
          float w_k = std::max(1.f - std::abs(1.f - d_c), 0.f);
          //w_k = 1.f;
          M_w.row(k) = w_k * (pm.cloud_->points[idx].getVector3fMap() - c);
          sum_w += w_k;
      }

      Eigen::Matrix3f scatter;
      scatter.setZero ();
      scatter = M_w.transpose() * M_w;

      Eigen::JacobiSVD<Eigen::MatrixXf> svd(scatter, Eigen::ComputeFullV);
      //std::cout << svd.matrixV() << std::endl;

      Eigen::Vector3f n = svd.matrixV().col(2);
      //flip normal if required
      if(n.dot(c*-1) < 0)
          n = n * -1.f;

      float d = n.dot(c) * -1.f;
      //std::cout << "normal:" << n << std::endl;
      //std::cout << "d:" << d << std::endl;

      pm.coefficients_.values[0] = n[0];
      pm.coefficients_.values[1] = n[1];
      pm.coefficients_.values[2] = n[2];
      pm.coefficients_.values[3] = d;

      pcl::PointIndices clean_inlier_indices;
      float dist_threshold_ = 0.01f;

      for(size_t k=0; k < inlier_indices[i].indices.size(); k++)
      {
          const int &idx = inlier_indices[i].indices[k];
          Eigen::Vector3f p = pm.cloud_->points[idx].getVector3fMap();
          float val = n.dot(p) + d;

          if(std::abs(val) <= dist_threshold_)
              clean_inlier_indices.indices.push_back( idx );
      }

      pm.inliers_ = clean_inlier_indices;
      models_.push_back(pm);
    }
  }
  else
  {
    // Create the filtering object: downsample the dataset using a leaf size of 1cm
    pcl::VoxelGrid<PointT> vg;
    PointTCloudPtr cloud_filtered (new PointTCloud);
    vg.setInputCloud (input_);
    float leaf_size_ = 0.005f;
    float dist_threshold_ = 0.01f;
    vg.setLeafSize (leaf_size_, leaf_size_, leaf_size_);
    vg.filter (*cloud_filtered);

    std::vector<bool> pixel_has_not_been_labelled( cloud_filtered->points.size(), true );

    // Create the segmentation object for the planar model and set all the parameters
    pcl::SACSegmentation<PointT> seg;
    pcl::ModelCoefficients coefficients;
    seg.setOptimizeCoefficients (true);
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setMaxIterations (1000);
    seg.setDistanceThreshold (dist_threshold_);

    PointTCloudPtr cloud_filtered_leftover (new PointTCloud (*cloud_filtered));

    while (1)
    {
      // Segment the largest planar component from the remaining cloud
      seg.setInputCloud (cloud_filtered_leftover);
      pcl::PointIndices inliers_in_leftover;
      seg.segment (inliers_in_leftover, coefficients);

      std::cout << "inliers in left over: " << inliers_in_leftover.indices.size() << " of " << cloud_filtered_leftover->points.size() << std::endl;

      if ( (int)inliers_in_leftover.indices.size () < min_plane_inliers_) // Could not estimate a(nother) planar model big enough for the given cloud.
        break;


      // make indices correspond to complete downsampled cloud
      pcl::PointIndices indices_in_original_cloud;
      size_t current_index_in_leftover = 0;
      size_t px=0;
      indices_in_original_cloud.indices.resize(inliers_in_leftover.indices.size());
      for(size_t inl_id=0; inl_id < inliers_in_leftover.indices.size(); inl_id++) {    // assumes indices are sorted in ascending order
          bool found = false;
          do {
              if( pixel_has_not_been_labelled[px] ) {
                  if( current_index_in_leftover == inliers_in_leftover.indices [inl_id] ) {
                      indices_in_original_cloud.indices[ inl_id ] = px;
                      found = true;
                  }
                  current_index_in_leftover++;
              }
              px++;
          } while( !found );
      }

      for(size_t i=0; i<indices_in_original_cloud.indices.size(); i++)
          pixel_has_not_been_labelled[ indices_in_original_cloud.indices[i] ] = false;


      //save coefficients
        PlaneModel<PointT> pm;
        pm.coefficients_ = coefficients;
        pm.cloud_ = cloud_filtered;
        pm.inliers_ = indices_in_original_cloud;
        models_.push_back(pm);

        pcl::copyPointCloud(*cloud_filtered, pixel_has_not_been_labelled, *cloud_filtered_leftover);
    }

    std::cout << "Number of planes found:" << models_.size() << "organized:" << static_cast<int>(input_->isOrganized() && !force_unorganized) << std::endl;
  }
}