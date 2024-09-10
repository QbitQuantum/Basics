void jsk_pcl_ros::DepthImageCreator::publish_points(const sensor_msgs::CameraInfoConstPtr& info,
                                                    const sensor_msgs::PointCloud2ConstPtr& pcloud2) {
  JSK_ROS_DEBUG("DepthImageCreator::publish_points");
  if (!pcloud2)  return;
  bool proc_cloud = true, proc_image = true, proc_disp = true;
  if ( pub_cloud_.getNumSubscribers()==0 ) {
    proc_cloud = false;
  }
  if ( pub_image_.getNumSubscribers()==0 ) {
    proc_image = false;
  }
  if ( pub_disp_image_.getNumSubscribers()==0 ) {
    proc_disp = false;
  }
  if( !proc_cloud && !proc_image && !proc_disp) return;

  int width = info->width;
  int height = info->height;
  float fx = info->P[0];
  float cx = info->P[2];
  float tx = info->P[3];
  float fy = info->P[5];
  float cy = info->P[6];

  Eigen::Affine3f sensorPose;
  {
    tf::StampedTransform transform;
    if(use_fixed_transform) {
      transform = fixed_transform;
    } else {
      try {
        tf_listener_->waitForTransform(pcloud2->header.frame_id,
                                       info->header.frame_id,
                                       info->header.stamp,
                                       ros::Duration(0.001));
        tf_listener_->lookupTransform(pcloud2->header.frame_id,
                                      info->header.frame_id,
                                      info->header.stamp, transform);
      }
      catch ( std::runtime_error e ) {
        JSK_ROS_ERROR("%s",e.what());
        return;
      }
    }
    tf::Vector3 p = transform.getOrigin();
    tf::Quaternion q = transform.getRotation();
    sensorPose = (Eigen::Affine3f)Eigen::Translation3f(p.getX(), p.getY(), p.getZ());
    Eigen::Quaternion<float> rot(q.getW(), q.getX(), q.getY(), q.getZ());
    sensorPose = sensorPose * rot;

    if (tx != 0.0) {
      Eigen::Affine3f trans = (Eigen::Affine3f)Eigen::Translation3f(-tx/fx , 0, 0);
      sensorPose = sensorPose * trans;
    }
#if 0 // debug print
    JSK_ROS_INFO("%f %f %f %f %f %f %f %f %f, %f %f %f",
             sensorPose(0,0), sensorPose(0,1), sensorPose(0,2),
             sensorPose(1,0), sensorPose(1,1), sensorPose(1,2),
             sensorPose(2,0), sensorPose(2,1), sensorPose(2,2),
             sensorPose(0,3), sensorPose(1,3), sensorPose(2,3));
#endif
  }

  PointCloud pointCloud;
  pcl::RangeImagePlanar rangeImageP;
  {
    // code here is dirty, some bag is in RangeImagePlanar
    PointCloud tpc;
    pcl::fromROSMsg(*pcloud2, tpc);

    Eigen::Affine3f inv;
#if ( PCL_MAJOR_VERSION >= 1 && PCL_MINOR_VERSION >= 5 )
    inv = sensorPose.inverse();
    pcl::transformPointCloud< Point > (tpc, pointCloud, inv);
#else
    pcl::getInverse(sensorPose, inv);
    pcl::getTransformedPointCloud<PointCloud> (tpc, inv, pointCloud);
#endif

    Eigen::Affine3f dummytrans;
    dummytrans.setIdentity();
    rangeImageP.createFromPointCloudWithFixedSize (pointCloud,
                                                   width/scale_depth, height/scale_depth,
                                                   cx/scale_depth, cy/scale_depth,
                                                   fx/scale_depth, fy/scale_depth,
                                                   dummytrans); //sensorPose);
  }

  cv::Mat mat(rangeImageP.height, rangeImageP.width, CV_32FC1);
  float *tmpf = (float *)mat.ptr();
  for(unsigned int i = 0; i < rangeImageP.height*rangeImageP.width; i++) {
    tmpf[i] = rangeImageP.points[i].z;
  }

  if(scale_depth != 1.0) {
    cv::Mat tmpmat(info->height, info->width, CV_32FC1);
    cv::resize(mat, tmpmat, cv::Size(info->width, info->height)); // LINEAR
    //cv::resize(mat, tmpmat, cv::Size(info->width, info->height), 0.0, 0.0, cv::INTER_NEAREST);
    mat = tmpmat;
  }

  if (proc_image) {
    sensor_msgs::Image pubimg;
    pubimg.header = info->header;
    pubimg.width = info->width;
    pubimg.height = info->height;
    pubimg.encoding = "32FC1";
    pubimg.step = sizeof(float)*info->width;
    pubimg.data.resize(sizeof(float)*info->width*info->height);

    // publish image
    memcpy(&(pubimg.data[0]), mat.ptr(), sizeof(float)*info->height*info->width);
    pub_image_.publish(boost::make_shared<sensor_msgs::Image>(pubimg));
  }

  if(proc_cloud || proc_disp) {
    // publish point cloud
    pcl::RangeImagePlanar rangeImagePP;
    rangeImagePP.setDepthImage ((float *)mat.ptr(),
                                width, height,
                                cx, cy, fx, fy);
#if PCL_MAJOR_VERSION == 1 && PCL_MINOR_VERSION >= 7
    rangeImagePP.header = pcl_conversions::toPCL(info->header);
#else
    rangeImagePP.header = info->header;
#endif
    if(proc_cloud) {
      pub_cloud_.publish(boost::make_shared<pcl::PointCloud<pcl::PointWithRange > >
                         ( (pcl::PointCloud<pcl::PointWithRange>)rangeImagePP) );
    }

    if(proc_disp) {
      stereo_msgs::DisparityImage disp;
#if PCL_MAJOR_VERSION == 1 && PCL_MINOR_VERSION >= 7
      disp.header = pcl_conversions::fromPCL(rangeImagePP.header);
#else
      disp.header = rangeImagePP.header;
#endif
      disp.image.encoding  = sensor_msgs::image_encodings::TYPE_32FC1;
      disp.image.height    = rangeImagePP.height;
      disp.image.width     = rangeImagePP.width;
      disp.image.step      = disp.image.width * sizeof(float);
      disp.f = fx; disp.T = 0.075;
      disp.min_disparity = 0;
      disp.max_disparity = disp.T * disp.f / 0.3;
      disp.delta_d = 0.125;

      disp.image.data.resize (disp.image.height * disp.image.step);
      float *data = reinterpret_cast<float*> (&disp.image.data[0]);

      float normalization_factor = disp.f * disp.T;
      for (int y = 0; y < (int)rangeImagePP.height; y++ ) {
        for (int x = 0; x < (int)rangeImagePP.width; x++ ) {
          pcl::PointWithRange p = rangeImagePP.getPoint(x,y);
          data[y*disp.image.width+x] = normalization_factor / p.z;
        }
      }
      pub_disp_image_.publish(boost::make_shared<stereo_msgs::DisparityImage> (disp));
    }
  }
}