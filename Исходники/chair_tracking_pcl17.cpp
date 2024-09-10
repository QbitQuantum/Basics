  void
  cloud_cb (const sensor_msgs::LaserScan::ConstPtr& scan)
  {
    sensor_msgs::PointCloud2 point_cloud2;
    RefCloudPtr raw_cloud(new RefCloud);

    projector_.transformLaserScanToPointCloud("base_laser_link", *scan, point_cloud2, tfListener_);
    pcl17::fromROSMsg<PointType> (point_cloud2, *raw_cloud);


    boost::mutex::scoped_lock lock (mtx_);
    cloud_pass_.reset (new Cloud);
    cloud_pass_downsampled_.reset (new Cloud);
    pcl17::ModelCoefficients::Ptr coefficients (new pcl17::ModelCoefficients ());
    pcl17::PointIndices::Ptr inliers (new pcl17::PointIndices ());
    filterPassThrough (raw_cloud, *cloud_pass_);
    if (counter_ < 10)
      {
        gridSample (cloud_pass_, *cloud_pass_downsampled_, downsampling_grid_size_);
      }
    else if (counter_ == 10)
      {
        //gridSample (cloud_pass_, *cloud_pass_downsampled_, 0.01);
        cloud_pass_downsampled_ = cloud_pass_;
        CloudPtr target_cloud;

        if (target_cloud != NULL)
          {

            RefCloudPtr nonzero_ref (new RefCloud);
            removeZeroPoints (input_model_point_cloud_, *nonzero_ref);

            //					PCL_INFO ("calculating cog\n");

            Eigen::Vector4f c;
            RefCloudPtr transed_ref (new RefCloud);
            pcl17::compute3DCentroid<RefPointType> (*nonzero_ref, c);
            Eigen::Affine3f trans = Eigen::Affine3f::Identity ();
            trans.translation ().matrix () = Eigen::Vector3f (c[0], c[1], c[2]);
            pcl17::transformPointCloud<RefPointType> (*nonzero_ref, *transed_ref, trans.inverse());
            CloudPtr transed_ref_downsampled (new Cloud);
            gridSample (transed_ref, *transed_ref_downsampled, downsampling_grid_size_);
            tracker_->setReferenceCloud (transed_ref_downsampled);
            tracker_->setTrans (trans);	
            tracker_->setMinIndices (int (input_model_point_cloud_->points.size ()) / 2);
          }
        else
          {
            //					PCL_WARN ("euclidean segmentation failed\n");
          }
      }
    else
      {

        gridSampleApprox (cloud_pass_, *cloud_pass_downsampled_, downsampling_grid_size_);
        tracking (cloud_pass_downsampled_);
      }
    
    new_cloud_ = true;
    counter_++;
  }