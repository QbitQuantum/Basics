  void
  ParticleFilterTracking::resetTrackingTargetModel(const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &new_target_cloud)
  {
    //prepare the model of tracker's target
    Eigen::Vector4f c;
    Eigen::Affine3f trans = Eigen::Affine3f::Identity ();
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr transed_ref (new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr transed_ref_downsampled (new pcl::PointCloud<pcl::PointXYZRGBA>);

    pcl::compute3DCentroid (*new_target_cloud, c);
    trans.translation ().matrix () = Eigen::Vector3f (c[0], c[1], c[2]);
    pcl::transformPointCloud(*new_target_cloud, *transed_ref, trans.inverse());
    gridSampleApprox (transed_ref, *transed_ref_downsampled, downsampling_grid_size_);
    //set reference model and trans
    {
      boost::mutex::scoped_lock lock(mtx_);
      tracker_->setReferenceCloud (transed_ref_downsampled);
      tracker_->setTrans (trans);
      tracker_->resetTracking();
    }
    //Reset target Model
    ROS_INFO("RESET TARGET MODEL");
  }