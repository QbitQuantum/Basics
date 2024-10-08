template<typename PointType> void
pcl::apps::DominantPlaneSegmentation<PointType>::compute_fast (std::vector<CloudPtr> & clusters)
{
  // Has the input dataset been set already?
  if (!input_)
  {
    PCL_WARN ("[pcl::apps::DominantPlaneSegmentation] No input dataset given!\n");
    return;
  }

  // Is the input dataset organized?
  if (input_->is_dense)
  {
    PCL_WARN ("[pcl::apps::DominantPlaneSegmentation] compute_fast can only be used with organized point clouds!\n");
    return;
  }

  CloudConstPtr cloud_;
  CloudPtr cloud_filtered_ (new Cloud ());
  CloudPtr cloud_downsampled_ (new Cloud ());
  pcl::PointCloud<pcl::Normal>::Ptr cloud_normals_ (new pcl::PointCloud<pcl::Normal> ());
  pcl::PointIndices::Ptr table_inliers_ (new pcl::PointIndices ());
  pcl::ModelCoefficients::Ptr table_coefficients_ (new pcl::ModelCoefficients ());
  CloudPtr table_projected_ (new Cloud ());
  CloudPtr table_hull_ (new Cloud ());
  CloudPtr cloud_objects_ (new Cloud ());
  CloudPtr cluster_object_ (new Cloud ());

  typename pcl::search::KdTree<PointType>::Ptr normals_tree_ (new pcl::search::KdTree<PointType>);
  typename pcl::search::KdTree<PointType>::Ptr clusters_tree_ (new pcl::search::KdTree<PointType>);
  clusters_tree_->setEpsilon (1);

  // Normal estimation parameters
  n3d_.setKSearch (k_);
  n3d_.setSearchMethod (normals_tree_);

  // Table model fitting parameters
  seg_.setDistanceThreshold (sac_distance_threshold_);
  seg_.setMaxIterations (2000);
  seg_.setNormalDistanceWeight (0.1);
  seg_.setOptimizeCoefficients (true);
  seg_.setModelType (pcl::SACMODEL_NORMAL_PLANE);
  seg_.setMethodType (pcl::SAC_RANSAC);
  seg_.setProbability (0.99);

  proj_.setModelType (pcl::SACMODEL_NORMAL_PLANE);
  bb_cluster_proj_.setModelType (pcl::SACMODEL_NORMAL_PLANE);

  prism_.setHeightLimits (object_min_height_, object_max_height_);

  // Clustering parameters
  cluster_.setClusterTolerance (object_cluster_tolerance_);
  cluster_.setMinClusterSize (object_cluster_min_size_);
  cluster_.setSearchMethod (clusters_tree_);

  // ---[ PassThroughFilter
  pass_.setFilterLimits (min_z_bounds_, max_z_bounds_);
  pass_.setFilterFieldName ("z");
  pass_.setInputCloud (input_);
  pass_.filter (*cloud_filtered_);

  if (int (cloud_filtered_->points.size ()) < k_)
  {
    PCL_WARN ("[DominantPlaneSegmentation] Filtering returned %zu points! Aborting.",
        cloud_filtered_->points.size ());
    return;
  }

  // Downsample the point cloud
  grid_.setLeafSize (downsample_leaf_, downsample_leaf_, downsample_leaf_);
  grid_.setDownsampleAllData (false);
  grid_.setInputCloud (cloud_filtered_);
  grid_.filter (*cloud_downsampled_);

  // ---[ Estimate the point normals
  n3d_.setInputCloud (cloud_downsampled_);
  n3d_.compute (*cloud_normals_);

  // ---[ Perform segmentation
  seg_.setInputCloud (cloud_downsampled_);
  seg_.setInputNormals (cloud_normals_);
  seg_.segment (*table_inliers_, *table_coefficients_);

  if (table_inliers_->indices.size () == 0)
  {
    PCL_WARN ("[DominantPlaneSegmentation] No Plane Inliers points! Aborting.");
    return;
  }

  // ---[ Extract the plane
  proj_.setInputCloud (cloud_downsampled_);
  proj_.setIndices (table_inliers_);
  proj_.setModelCoefficients (table_coefficients_);
  proj_.filter (*table_projected_);

  // ---[ Estimate the convex hull
  std::vector<pcl::Vertices> polygons;
  CloudPtr table_hull (new Cloud ());
  hull_.setInputCloud (table_projected_);
  hull_.reconstruct (*table_hull, polygons);

  // Compute the plane coefficients
  Eigen::Vector4f model_coefficients;
  EIGEN_ALIGN16 Eigen::Matrix3f covariance_matrix;

  model_coefficients[0] = table_coefficients_->values[0];
  model_coefficients[1] = table_coefficients_->values[1];
  model_coefficients[2] = table_coefficients_->values[2];
  model_coefficients[3] = table_coefficients_->values[3];

  // Need to flip the plane normal towards the viewpoint
  Eigen::Vector4f vp (0, 0, 0, 0);
  // See if we need to flip any plane normals
  vp -= table_hull->points[0].getVector4fMap ();
  vp[3] = 0;
  // Dot product between the (viewpoint - point) and the plane normal
  float cos_theta = vp.dot (model_coefficients);
  // Flip the plane normal
  if (cos_theta < 0)
  {
    model_coefficients *= -1;
    model_coefficients[3] = 0;
    // Hessian form (D = nc . p_plane (centroid here) + p)
    model_coefficients[3] = -1 * (model_coefficients.dot (table_hull->points[0].getVector4fMap ()));
  }

  //Set table_coeffs
  table_coeffs_ = model_coefficients;

  // ---[ Get the objects on top of the table
  pcl::PointIndices cloud_object_indices;
  prism_.setInputCloud (input_);
  prism_.setInputPlanarHull (table_hull);
  prism_.segment (cloud_object_indices);

  pcl::ExtractIndices<PointType> extract_object_indices;
  extract_object_indices.setInputCloud (input_);
  extract_object_indices.setIndices (boost::make_shared<const pcl::PointIndices> (cloud_object_indices));
  extract_object_indices.filter (*cloud_objects_);

  //create new binary pointcloud with intensity values (0 and 1), 0 for non-object pixels and 1 otherwise
  pcl::PointCloud<pcl::PointXYZI>::Ptr binary_cloud (new pcl::PointCloud<pcl::PointXYZI>);

  {
    binary_cloud->width = input_->width;
    binary_cloud->height = input_->height;
    binary_cloud->points.resize (input_->points.size ());
    binary_cloud->is_dense = input_->is_dense;

    size_t idx;
    for (size_t i = 0; i < cloud_object_indices.indices.size (); ++i)
    {
      idx = cloud_object_indices.indices[i];
      binary_cloud->points[idx].getVector4fMap () = input_->points[idx].getVector4fMap ();
      binary_cloud->points[idx].intensity = 1.0;
    }
  }

  //connected components on the binary image

  std::map<float, float> connected_labels;
  float c_intensity = 0.1f;
  float intensity_incr = 0.1f;

  {

    int wsize = wsize_;
    for (int i = 0; i < int (binary_cloud->width); i++)
    {
      for (int j = 0; j < int (binary_cloud->height); j++)
      {
        if (binary_cloud->at (i, j).intensity != 0)
        {
          //check neighboring pixels, first left and then top
          //be aware of margins

          if ((i - 1) < 0 && (j - 1) < 0)
          {
            //top-left pixel
            (*binary_cloud) (i, j).intensity = c_intensity;
          }
          else
          {
            if ((j - 1) < 0)
            {
              //top-row, check on the left of pixel to assign a new label or not
              int left = check ((*binary_cloud) (i - 1, j), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);
              if (left)
              {
                //Nothing found on the left, check bigger window

                bool found = false;
                for (int kk = 2; kk < wsize && !found; kk++)
                {
                  if ((i - kk) < 0)
                    continue;

                  int left = check ((*binary_cloud) (i - kk, j), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);
                  if (left == 0)
                  {
                    found = true;
                  }
                }

                if (!found)
                {
                  c_intensity += intensity_incr;
                  (*binary_cloud) (i, j).intensity = c_intensity;
                }

              }
            }
            else
            {
              if ((i - 1) == 0)
              {
                //check only top
                int top = check ((*binary_cloud) (i, j - 1), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);
                if (top)
                {
                  bool found = false;
                  for (int kk = 2; kk < wsize && !found; kk++)
                  {
                    if ((j - kk) < 0)
                      continue;

                    int top = check ((*binary_cloud) (i, j - kk), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);
                    if (top == 0)
                    {
                      found = true;
                    }
                  }

                  if (!found)
                  {
                    c_intensity += intensity_incr;
                    (*binary_cloud) (i, j).intensity = c_intensity;
                  }
                }

              }
              else
              {
                //check left and top
                int left = check ((*binary_cloud) (i - 1, j), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);
                int top = check ((*binary_cloud) (i, j - 1), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);

                if (left == 0 && top == 0)
                {
                  //both top and left had labels, check if they are different
                  //if they are, take the smallest one and mark labels to be connected..

                  if ((*binary_cloud) (i - 1, j).intensity != (*binary_cloud) (i, j - 1).intensity)
                  {
                    float smaller_intensity = (*binary_cloud) (i - 1, j).intensity;
                    float bigger_intensity = (*binary_cloud) (i, j - 1).intensity;

                    if ((*binary_cloud) (i - 1, j).intensity > (*binary_cloud) (i, j - 1).intensity)
                    {
                      smaller_intensity = (*binary_cloud) (i, j - 1).intensity;
                      bigger_intensity = (*binary_cloud) (i - 1, j).intensity;
                    }

                    connected_labels[bigger_intensity] = smaller_intensity;
                    (*binary_cloud) (i, j).intensity = smaller_intensity;
                  }
                }

                if (left == 1 && top == 1)
                {
                  //if none had labels, increment c_intensity
                  //search first on bigger window
                  bool found = false;
                  for (int dist = 2; dist < wsize && !found; dist++)
                  {
                    if (((i - dist) < 0) || ((j - dist) < 0))
                      continue;

                    int left = check ((*binary_cloud) (i - dist, j), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);
                    int top = check ((*binary_cloud) (i, j - dist), (*binary_cloud) (i, j), c_intensity, object_cluster_tolerance_);

                    if (left == 0 && top == 0)
                    {
                      if ((*binary_cloud) (i - dist, j).intensity != (*binary_cloud) (i, j - dist).intensity)
                      {
                        float smaller_intensity = (*binary_cloud) (i - dist, j).intensity;
                        float bigger_intensity = (*binary_cloud) (i, j - dist).intensity;

                        if ((*binary_cloud) (i - dist, j).intensity > (*binary_cloud) (i, j - dist).intensity)
                        {
                          smaller_intensity = (*binary_cloud) (i, j - dist).intensity;
                          bigger_intensity = (*binary_cloud) (i - dist, j).intensity;
                        }

                        connected_labels[bigger_intensity] = smaller_intensity;
                        (*binary_cloud) (i, j).intensity = smaller_intensity;
                        found = true;
                      }
                    }
                    else if (left == 0 || top == 0)
                    {
                      //one had label
                      found = true;
                    }
                  }

                  if (!found)
                  {
                    //none had label in the bigger window
                    c_intensity += intensity_incr;
                    (*binary_cloud) (i, j).intensity = c_intensity;
                  }
                }
              }
            }
          }

        }
      }
    }
  }

  std::map<float, pcl::PointIndices> clusters_map;

  {
    std::map<float, float>::iterator it;

    for (int i = 0; i < int (binary_cloud->width); i++)
    {
      for (int j = 0; j < int (binary_cloud->height); j++)
      {
        if (binary_cloud->at (i, j).intensity != 0)
        {
          //check if this is a root label...
          it = connected_labels.find (binary_cloud->at (i, j).intensity);
          while (it != connected_labels.end ())
          {
            //the label is on the list, change pixel intensity until it has a root label
            (*binary_cloud) (i, j).intensity = (*it).second;
            it = connected_labels.find (binary_cloud->at (i, j).intensity);
          }

          std::map<float, pcl::PointIndices>::iterator it_indices;
          it_indices = clusters_map.find (binary_cloud->at (i, j).intensity);
          if (it_indices == clusters_map.end ())
          {
            pcl::PointIndices indices;
            clusters_map[binary_cloud->at (i, j).intensity] = indices;
          }

          clusters_map[binary_cloud->at (i, j).intensity].indices.push_back (static_cast<int> (j * binary_cloud->width + i));
        }
      }
    }
  }

  clusters.resize (clusters_map.size ());

  std::map<float, pcl::PointIndices>::iterator it_indices;
  int k = 0;
  for (it_indices = clusters_map.begin (); it_indices != clusters_map.end (); it_indices++)
  {

    if (int ((*it_indices).second.indices.size ()) >= object_cluster_min_size_)
    {

      clusters[k] = CloudPtr (new Cloud ());
      pcl::copyPointCloud (*input_, (*it_indices).second.indices, *clusters[k]);
      k++;
      indices_clusters_.push_back((*it_indices).second);
    }
  }

  clusters.resize (k);

}