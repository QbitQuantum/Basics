  void callback(const tPointCloud::ConstPtr& rgb_cloud, 
                const tImage::ConstPtr& rgb_image, 
                const tCameraInfo::ConstPtr& rgb_caminfo,
                const tImage::ConstPtr& depth_image, 
                const tPointCloud::ConstPtr& cloud
                )
  {
    if (max_update_rate_ > 0.0)
    {
      NODELET_DEBUG("update set to %f", max_update_rate_);
      if ( last_update_ + ros::Duration(1.0/max_update_rate_) > ros::Time::now())
      {
        NODELET_DEBUG("throttle last update at %f skipping", last_update_.toSec());
        return;
      }
    }
    else
      NODELET_DEBUG("update_rate unset continuing");

    last_update_ = ros::Time::now();

    rgb_cloud_pub_.publish(rgb_cloud);
    rgb_image_pub_.publish(rgb_image);
    rgb_caminfo_pub_.publish(rgb_caminfo);
    depth_image_pub_.publish(depth_image);
    cloud_pub_.publish(cloud);
  }