  void PointCloudLocalization::cloudCallback(
    const sensor_msgs::PointCloud2::ConstPtr& cloud_msg)
  {
    vital_checker_->poke();
    boost::mutex::scoped_lock lock(mutex_);
    //JSK_NODELET_INFO("cloudCallback");
    latest_cloud_ = cloud_msg;
    if (localize_requested_){
      JSK_NODELET_INFO("localization is requested");
      try {
        pcl::PointCloud<pcl::PointNormal>::Ptr
          local_cloud (new pcl::PointCloud<pcl::PointNormal>);
        pcl::fromROSMsg(*latest_cloud_, *local_cloud);
        JSK_NODELET_INFO("waiting for tf transformation from %s tp %s",
                     latest_cloud_->header.frame_id.c_str(),
                     global_frame_.c_str());
        if (tf_listener_->waitForTransform(
              latest_cloud_->header.frame_id,
              global_frame_,
              latest_cloud_->header.stamp,
              ros::Duration(1.0))) {
          pcl::PointCloud<pcl::PointNormal>::Ptr
            input_cloud (new pcl::PointCloud<pcl::PointNormal>);
          if (use_normal_) {
            pcl_ros::transformPointCloudWithNormals(global_frame_,
                                                    *local_cloud,
                                                    *input_cloud,
                                                    *tf_listener_);
          }
          else {
            pcl_ros::transformPointCloud(global_frame_,
                                         *local_cloud,
                                         *input_cloud,
                                         *tf_listener_);
          }
          pcl::PointCloud<pcl::PointNormal>::Ptr
            input_downsampled_cloud (new pcl::PointCloud<pcl::PointNormal>);
          applyDownsampling(input_cloud, *input_downsampled_cloud);
          if (isFirstTime()) {
            all_cloud_ = input_downsampled_cloud;
            first_time_ = false;
          }
          else {
            // run ICP
            ros::ServiceClient client
              = pnh_->serviceClient<jsk_pcl_ros::ICPAlign>("icp_align");
            jsk_pcl_ros::ICPAlign icp_srv;

            if (clip_unseen_pointcloud_) {
              // Before running ICP, remove pointcloud where we cannot see
              // First, transform reference pointcloud, that is all_cloud_, into
              // sensor frame.
              // And after that, remove points which are x < 0.
              tf::StampedTransform global_sensor_tf_transform
                = lookupTransformWithDuration(
                  tf_listener_,
                  global_frame_,
                  sensor_frame_,
                  cloud_msg->header.stamp,
                  ros::Duration(1.0));
              Eigen::Affine3f global_sensor_transform;
              tf::transformTFToEigen(global_sensor_tf_transform,
                                     global_sensor_transform);
              pcl::PointCloud<pcl::PointNormal>::Ptr sensor_cloud
                (new pcl::PointCloud<pcl::PointNormal>);
              pcl::transformPointCloudWithNormals(
                *all_cloud_,
                *sensor_cloud,
                global_sensor_transform.inverse());
              // Remove negative-x points
              pcl::PassThrough<pcl::PointNormal> pass;
              pass.setInputCloud(sensor_cloud);
              pass.setFilterFieldName("x");
              pass.setFilterLimits(0.0, 100.0);
              pcl::PointCloud<pcl::PointNormal>::Ptr filtered_cloud
                (new pcl::PointCloud<pcl::PointNormal>);
              pass.filter(*filtered_cloud);
              JSK_NODELET_INFO("clipping: %lu -> %lu", sensor_cloud->points.size(), filtered_cloud->points.size());
              // Convert the pointcloud to global frame again
              pcl::PointCloud<pcl::PointNormal>::Ptr global_filtered_cloud
                (new pcl::PointCloud<pcl::PointNormal>);
              pcl::transformPointCloudWithNormals(
                *filtered_cloud,
                *global_filtered_cloud,
                global_sensor_transform);
              pcl::toROSMsg(*global_filtered_cloud,
                            icp_srv.request.target_cloud);
            }
            else {
              pcl::toROSMsg(*all_cloud_,
                            icp_srv.request.target_cloud);
            }
            pcl::toROSMsg(*input_downsampled_cloud,
                          icp_srv.request.reference_cloud);
            
            if (client.call(icp_srv)) {
              Eigen::Affine3f transform;
              tf::poseMsgToEigen(icp_srv.response.result.pose, transform);
              Eigen::Vector3f transform_pos(transform.translation());
              float roll, pitch, yaw;
              pcl::getEulerAngles(transform, roll, pitch, yaw);
              JSK_NODELET_INFO("aligned parameter --");
              JSK_NODELET_INFO("  - pos: [%f, %f, %f]",
                           transform_pos[0],
                           transform_pos[1],
                           transform_pos[2]);
              JSK_NODELET_INFO("  - rot: [%f, %f, %f]", roll, pitch, yaw);
              pcl::PointCloud<pcl::PointNormal>::Ptr
                transformed_input_cloud (new pcl::PointCloud<pcl::PointNormal>);
              if (use_normal_) {
                pcl::transformPointCloudWithNormals(*input_cloud,
                                                    *transformed_input_cloud,
                                                    transform);
              }
              else {
                pcl::transformPointCloud(*input_cloud,
                                         *transformed_input_cloud,
                                         transform);
              }
              pcl::PointCloud<pcl::PointNormal>::Ptr
                concatenated_cloud (new pcl::PointCloud<pcl::PointNormal>);
              *concatenated_cloud = *all_cloud_ + *transformed_input_cloud;
              // update *all_cloud
              applyDownsampling(concatenated_cloud, *all_cloud_);
              // update localize_transform_
              tf::Transform icp_transform;
              tf::transformEigenToTF(transform, icp_transform);
              {
                boost::mutex::scoped_lock tf_lock(tf_mutex_);
                localize_transform_ = localize_transform_ * icp_transform;
              }
            }
            else {
              JSK_NODELET_ERROR("Failed to call ~icp_align");
              return;
            }
          }
          localize_requested_ = false;
        }
        else {
          JSK_NODELET_WARN("No tf transformation is available");
        }
      }
      catch (tf2::ConnectivityException &e)
      {
        JSK_NODELET_ERROR("[%s] Transform error: %s", __PRETTY_FUNCTION__, e.what());
        return;
      }
      catch (tf2::InvalidArgumentException &e)
      {
        JSK_NODELET_ERROR("[%s] Transform error: %s", __PRETTY_FUNCTION__, e.what());
        return;
      }
    }
  }