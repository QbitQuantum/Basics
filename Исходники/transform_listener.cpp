void TransformListener::transformPointCloud(const std::string & target_frame, const tf::Transform& net_transform,
                                            const ros::Time& target_time, const sensor_msgs::PointCloud & cloudIn, 
                                            sensor_msgs::PointCloud & cloudOut) const
{
  tf::Vector3 origin = net_transform.getOrigin();
  tf::Matrix3x3 basis  = net_transform.getBasis();

  unsigned int length = cloudIn.points.size();

  // Copy relevant data from cloudIn, if needed
  if (&cloudIn != &cloudOut)
  {
    cloudOut.header = cloudIn.header;
    cloudOut.points.resize(length);
    cloudOut.channels.resize(cloudIn.channels.size());
    for (unsigned int i = 0 ; i < cloudIn.channels.size() ; ++i)
      cloudOut.channels[i] = cloudIn.channels[i];
  }

  // Transform points
  cloudOut.header.stamp = target_time;
  cloudOut.header.frame_id = target_frame;
  for (unsigned int i = 0; i < length ; i++) {
    transformPointMatVec(origin, basis, cloudIn.points[i], cloudOut.points[i]);
  }
}