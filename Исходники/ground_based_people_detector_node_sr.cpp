void
computeBackgroundCloud (int frames, float voxel_size, int sr_conf_threshold, std::string frame_id, ros::Rate rate, PointCloudT::Ptr& background_cloud)
{
  std::cout << "Background acquisition..." << std::flush;

  // Create background cloud:
  PointCloudT::Ptr cloud_to_process(new PointCloudT);
  background_cloud->header = cloud->header;
  for (unsigned int i = 0; i < frames; i++)
  {
    *cloud_to_process = *cloud;

    // Remove low confidence points:
    removeLowConfidencePoints(confidence_image, sr_conf_threshold, cloud_to_process);

    // Voxel grid filtering:
    PointCloudT::Ptr cloud_filtered(new PointCloudT);
    pcl::VoxelGrid<PointT> voxel_grid_filter_object;
    voxel_grid_filter_object.setInputCloud(cloud_to_process);
    voxel_grid_filter_object.setLeafSize (voxel_size, voxel_size, voxel_size);
    voxel_grid_filter_object.filter (*cloud_filtered);

    *background_cloud += *cloud_filtered;
    ros::spinOnce();
    rate.sleep();
  }

  // Voxel grid filtering:
  PointCloudT::Ptr cloud_filtered(new PointCloudT);
  pcl::VoxelGrid<PointT> voxel_grid_filter_object;
  voxel_grid_filter_object.setInputCloud(background_cloud);
  voxel_grid_filter_object.setLeafSize (voxel_size, voxel_size, voxel_size);
  voxel_grid_filter_object.filter (*cloud_filtered);

  background_cloud = cloud_filtered;

  // Background saving:
  pcl::io::savePCDFileASCII ("/tmp/background_" + frame_id.substr(1, frame_id.length()-1) + ".pcd", *background_cloud);

  std::cout << "done." << std::endl << std::endl;
}