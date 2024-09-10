void VoNode::imgCb(const sensor_msgs::ImageConstPtr& msg)
{
  // Dummy data as the real position for the system.
//  static int old = msg->header.seq;
//  if(msg->header.seq == old)
//      filtered_pose.pose.position.z = 0;
//  else{
//      filtered_pose.pose.position.z += 10.0/70.0 * (msg->header.seq-old);
//  }
//  old = msg->header.seq;

  ROS_INFO("Frame seq: %i", msg->header.seq);

#ifdef USE_ASE_IMU
  tf::StampedTransform transform;
  try{
    listener_.lookupTransform("/camera", "/worldNED",
                           ros::Time(0), transform);
  }

  catch (tf::TransformException ex){
    ROS_ERROR("%s",ex.what());
    return;
  }
#endif

  cv::Mat img;
  try {
    img = cv_bridge::toCvShare(msg, "mono8")->image;
  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  }
  processUserActions();

//  Quaterniond quat(filtered_pose.pose.orientation.w,filtered_pose.pose.orientation.x,filtered_pose.pose.orientation.y, filtered_pose.pose.orientation.z);
//  Matrix3d orient = quat.toRotationMatrix();
//  Vector3d pos(filtered_pose.pose.position.x,filtered_pose.pose.position.y, filtered_pose.pose.position.z);

  Quaterniond quat;
  quat.setIdentity();
  Vector3d pos;
  pos.setZero();
  Matrix3d orient = quat.toRotationMatrix();

#ifdef USE_ASE_IMU
  tf::quaternionTFToEigen(transform.getRotation(), quat);
  orient = quat.toRotationMatrix();
  tf::vectorTFToEigen(transform.getOrigin(), pos);
#endif

  vo_->addImage(img, msg->header.stamp.toSec(), orient, pos);
  visualizer_.publishMinimal(img, vo_->lastFrame(), *vo_, msg->header.stamp.toSec());

  if(publish_markers_ && vo_->stage() != FrameHandlerBase::STAGE_PAUSED)
    visualizer_.visualizeMarkers(vo_->lastFrame(), vo_->coreKeyframes(), vo_->map());

  if(publish_dense_input_)
    visualizer_.exportToDense(vo_->lastFrame());

  if(vo_->stage() == FrameHandlerMono::STAGE_PAUSED)
    usleep(100000);
}