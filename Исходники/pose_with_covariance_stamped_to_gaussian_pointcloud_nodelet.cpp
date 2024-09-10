 void PoseWithCovarianceStampedToGaussianPointCloud::convert(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
 {
   boost::mutex::scoped_lock lock(mutex_);
   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
   Eigen::Vector2f mean;
   Eigen::Matrix2f S;
   if (cut_plane_ == "xy" || cut_plane_ == "flipped_xy") {
     mean = Eigen::Vector2f(msg->pose.pose.position.x, msg->pose.pose.position.y);
     S << msg->pose.covariance[0], msg->pose.covariance[1], 
       msg->pose.covariance[6], msg->pose.covariance[7];
   }
   else if (cut_plane_ == "yz" || cut_plane_ == "flipped_yz") {
     mean = Eigen::Vector2f(msg->pose.pose.position.y, msg->pose.pose.position.z);
     S << msg->pose.covariance[7], msg->pose.covariance[8], 
       msg->pose.covariance[13], msg->pose.covariance[14];
   }
   else if (cut_plane_ == "zx" || cut_plane_ == "flipped_zx") {
     mean = Eigen::Vector2f(msg->pose.pose.position.z, msg->pose.pose.position.x);
     S << msg->pose.covariance[14], msg->pose.covariance[12], 
       msg->pose.covariance[0], msg->pose.covariance[2];
   }
   double max_sigma = 0;
   for (size_t i = 0; i < 2; i++) {
     for (size_t j = 0; j < 2; j++) {
       double sigma = sqrt(S(i, j));
       if (max_sigma < sigma) {
         max_sigma = sigma;
       }
     }
   }
   Eigen::Matrix2f S_inv = S.inverse();
   double dx = 6.0 * max_sigma / sampling_num_;
   double dy = 6.0 * max_sigma / sampling_num_;
   for (double x = - 3.0 * max_sigma; x <= 3.0 * max_sigma; x += dx) {
     for (double y = - 3.0 * max_sigma; y <= 3.0 * max_sigma; y += dy) {
       Eigen::Vector2f diff(x, y);
       Eigen::Vector2f input = diff + mean;
       float z = gaussian(input, mean, S, S_inv);
       pcl::PointXYZ p;
       if (cut_plane_ == "xy") {
         p.x = input[0];
         p.y = input[1];
         p.z = z + msg->pose.pose.position.z;
       }
       else if (cut_plane_ == "yz") {
         p.y = input[0];
         p.z = input[1];
         p.x = z + msg->pose.pose.position.x;
       }
       else if (cut_plane_ == "zx") {
         p.z = input[0];
         p.x = input[1];
         p.y = z + msg->pose.pose.position.y;
       }
       else if (cut_plane_ == "flipped_xy") {
         p.x = input[0];
         p.y = input[1];
         p.z = -z + msg->pose.pose.position.z;
       }
       else if (cut_plane_ == "flipped_yz") {
         p.y = input[0];
         p.z = input[1];
         p.x = -z + msg->pose.pose.position.x;
       }
       else if (cut_plane_ == "flipped_zx") {
         p.z = input[0];
         p.x = input[1];
         p.y = -z + msg->pose.pose.position.y;
       }
       cloud->points.push_back(p);
     }
   }
   sensor_msgs::PointCloud2 ros_cloud;
   pcl::toROSMsg(*cloud, ros_cloud);
   ros_cloud.header = msg->header;
   pub_.publish(ros_cloud);
 }