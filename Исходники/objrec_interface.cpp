void ObjRecInterface::recognize_objects_thread()
{
  ros::Rate max_rate(100.0);

  // Working structures
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_full(new pcl::PointCloud<pcl::PointXYZRGB>());
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
  boost::shared_ptr<pcl::VoxelGrid<pcl::PointXYZRGB> > voxel_grid(new pcl::VoxelGrid<pcl::PointXYZRGB>());

  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
  pcl::PointIndices::Ptr outliers (new pcl::PointIndices);

  // Create point clouds for foreground and background points
  vtkSmartPointer<vtkPoints> foreground_points;
  foreground_points.TakeReference(vtkPoints::New(VTK_DOUBLE));

  std::list<boost::shared_ptr<PointSetShape> > detected_models;

  while(ros::ok() && !time_to_stop_)
  {
    // Don't hog the cpu
    max_rate.sleep();

    cloud_full->clear();
    cloud->clear();

    ROS_DEBUG_STREAM("ObjRec: Aggregating point clouds... ");
    {
      // Scope for syncrhonization

      // Continue if the cloud is empty
      static ros::Rate warn_rate(1.0);
      if(clouds_.empty()) {
        ROS_WARN("Pointcloud buffer is empty!");
        warn_rate.sleep();
        continue;
      }

      // Lock the buffer mutex
      boost::mutex::scoped_lock buffer_lock(buffer_mutex_);

      ROS_DEBUG_STREAM("ObjRec: Computing objects from "
          <<clouds_.size()<<" point clounds "
          <<"between "<<(ros::Time::now() - pcl_conversions::fromPCL(clouds_.back()->header).stamp)
          <<" to "<<(ros::Time::now() - pcl_conversions::fromPCL(clouds_.front()->header).stamp)<<" seconds after they were acquired.");

      // Copy references to the stored clouds
      cloud_full->header = clouds_.front()->header;

      for(std::list<boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB> > >::const_iterator it = clouds_.begin();
          it != clouds_.end();
          ++it)
      {
        *cloud_full += *(*it);
      }
    }

    // Recongize objects
    bool objects_recognized = this->recognize_objects(
        cloud_full,
        cloud,
        voxel_grid,
        coefficients, inliers, outliers,
        foreground_points,
        detected_models,
        true,
        true);

    // No objects recognized
    if(!objects_recognized) {
      continue;
    }

    // Construct recognized objects message
    objrec_msgs::RecognizedObjects objects_msg;
    objects_msg.header.stamp = pcl_conversions::fromPCL(cloud->header).stamp;
    objects_msg.header.frame_id = "/world";//cloud->header;

    for(std::list<boost::shared_ptr<PointSetShape> >::iterator it = detected_models.begin();
        it != detected_models.end();
        ++it)
    {
      boost::shared_ptr<PointSetShape> detected_model = *it;

      // Construct and populate a message
      objrec_msgs::PointSetShape pss_msg;
      pss_msg.label = detected_model->getUserData()->getLabel();
      pss_msg.confidence = detected_model->getConfidence();
      array_to_pose(detected_model->getRigidTransform(), pss_msg.pose);

      // Transform into the world frame TODO: make this frame a parameter
      geometry_msgs::PoseStamped pose_stamped_in, pose_stamped_out;
      pose_stamped_in.header = pcl_conversions::fromPCL(cloud->header);
      pose_stamped_in.pose = pss_msg.pose;

      try {
        listener_.transformPose("/world",pose_stamped_in,pose_stamped_out);
        pss_msg.pose = pose_stamped_out.pose;
      }
      catch (tf::TransformException ex){
        ROS_WARN("Not transforming recognized objects into world frame: %s",ex.what());
      }

      objects_msg.objects.push_back(pss_msg);
    }

    // Publish the visualization markers
    this->publish_markers(objects_msg);

    // Publish the recognized objects
    objects_pub_.publish(objects_msg);

    // Publish the points used in the scan, for debugging
    foreground_points_pub_.publish(cloud);
  }
}