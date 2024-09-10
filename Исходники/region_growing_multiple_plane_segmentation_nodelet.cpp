  void RegionGrowingMultiplePlaneSegmentation::segment(
    const sensor_msgs::PointCloud2::ConstPtr& msg,
    const sensor_msgs::PointCloud2::ConstPtr& normal_msg)
  {
    boost::mutex::scoped_lock lock(mutex_);
    if (!done_initialization_) {
      return;
    }
    vital_checker_->poke();
    {
      jsk_recognition_utils::ScopedWallDurationReporter r
        = timer_.reporter(pub_latest_time_, pub_average_time_);
      pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
      pcl::PointCloud<pcl::Normal>::Ptr normal(new pcl::PointCloud<pcl::Normal>);
      pcl::fromROSMsg(*msg, *cloud);
      pcl::fromROSMsg(*normal_msg, *normal);
      // concatenate fields
      pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr
        all_cloud (new pcl::PointCloud<pcl::PointXYZRGBNormal>);
      pcl::concatenateFields(*cloud, *normal, *all_cloud);
      pcl::PointIndices::Ptr indices (new pcl::PointIndices);
      for (size_t i = 0; i < all_cloud->points.size(); i++) {
        if (!isnan(all_cloud->points[i].x) &&
            !isnan(all_cloud->points[i].y) &&
            !isnan(all_cloud->points[i].z) &&
            !isnan(all_cloud->points[i].normal_x) &&
            !isnan(all_cloud->points[i].normal_y) &&
            !isnan(all_cloud->points[i].normal_z) &&
            !isnan(all_cloud->points[i].curvature)) {
          if (all_cloud->points[i].curvature < max_curvature_) {
            indices->indices.push_back(i);
          }
        }
      }
      pcl::ConditionalEuclideanClustering<pcl::PointXYZRGBNormal> cec (true);
    
      // vector of pcl::PointIndices
      pcl::IndicesClustersPtr clusters (new pcl::IndicesClusters);
      cec.setInputCloud (all_cloud);
      cec.setIndices(indices);
      cec.setClusterTolerance(cluster_tolerance_);
      cec.setMinClusterSize(min_size_);
      //cec.setMaxClusterSize(max_size_);
      {
        boost::mutex::scoped_lock lock2(global_custom_condigion_function_mutex);
        setCondifionFunctionParameter(angular_threshold_, distance_threshold_);
        cec.setConditionFunction(
          &RegionGrowingMultiplePlaneSegmentation::regionGrowingFunction);
        //ros::Time before = ros::Time::now();
        cec.segment (*clusters);
        // ros::Time end = ros::Time::now();
        // ROS_INFO("segment took %f sec", (before - end).toSec());
      }
      // Publish raw cluster information 
      // pcl::IndicesCluster is typdefed as std::vector<pcl::PointIndices>
      jsk_recognition_msgs::ClusterPointIndices ros_clustering_result;
      ros_clustering_result.cluster_indices
        = pcl_conversions::convertToROSPointIndices(*clusters, msg->header);
      ros_clustering_result.header = msg->header;
      pub_clustering_result_.publish(ros_clustering_result);

      // estimate planes
      std::vector<pcl::PointIndices::Ptr> all_inliers;
      std::vector<pcl::ModelCoefficients::Ptr> all_coefficients;
      jsk_recognition_msgs::PolygonArray ros_polygon;
      ros_polygon.header = msg->header;
      for (size_t i = 0; i < clusters->size(); i++) {
        pcl::PointIndices::Ptr plane_inliers(new pcl::PointIndices);
        pcl::ModelCoefficients::Ptr plane_coefficients(new pcl::ModelCoefficients);
        pcl::PointIndices::Ptr cluster = boost::make_shared<pcl::PointIndices>((*clusters)[i]);
        ransacEstimation(cloud, cluster,
                         *plane_inliers, *plane_coefficients);
        if (plane_inliers->indices.size() > 0) {
          jsk_recognition_utils::ConvexPolygon::Ptr convex
            = jsk_recognition_utils::convexFromCoefficientsAndInliers<pcl::PointXYZRGB>(
              cloud, plane_inliers, plane_coefficients);
          if (convex) {
            if (min_area_ > convex->area() || convex->area() > max_area_) {
              continue;
            }
            {
              // check direction consistency of coefficients and convex
              Eigen::Vector3f coefficient_normal(plane_coefficients->values[0],
                                                 plane_coefficients->values[1],
                                                 plane_coefficients->values[2]);
              if (convex->getNormalFromVertices().dot(coefficient_normal) < 0) {
                convex = boost::make_shared<jsk_recognition_utils::ConvexPolygon>(convex->flipConvex());
              }
            }
            // Normal should direct to origin
            {
              Eigen::Vector3f p = convex->getPointOnPlane();
              Eigen::Vector3f n = convex->getNormal();
              if (p.dot(n) > 0) {
                convex = boost::make_shared<jsk_recognition_utils::ConvexPolygon>(convex->flipConvex());
                Eigen::Vector3f new_normal = convex->getNormal();
                plane_coefficients->values[0] = new_normal[0];
                plane_coefficients->values[1] = new_normal[1];
                plane_coefficients->values[2] = new_normal[2];
                plane_coefficients->values[3] = convex->getD();
              }
            }
          
            geometry_msgs::PolygonStamped polygon;
            polygon.polygon = convex->toROSMsg();
            polygon.header = msg->header;
            ros_polygon.polygons.push_back(polygon);
            all_inliers.push_back(plane_inliers);
            all_coefficients.push_back(plane_coefficients);
          }
        }
      }
    
      jsk_recognition_msgs::ClusterPointIndices ros_indices;
      ros_indices.cluster_indices =
        pcl_conversions::convertToROSPointIndices(all_inliers, msg->header);
      ros_indices.header = msg->header;
      pub_inliers_.publish(ros_indices);
      jsk_recognition_msgs::ModelCoefficientsArray ros_coefficients;
      ros_coefficients.header = msg->header;
      ros_coefficients.coefficients =
        pcl_conversions::convertToROSModelCoefficients(
          all_coefficients, msg->header);
      pub_coefficients_.publish(ros_coefficients);
      pub_polygons_.publish(ros_polygon);
    }
  }