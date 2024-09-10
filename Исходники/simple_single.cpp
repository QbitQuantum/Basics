 // wait for one camerainfo, then shut down that subscriber
 void cam_info_callback(const sensor_msgs::CameraInfo &msg)
 {
   camParam = aruco_ros::rosCameraInfo2ArucoCamParams(msg, useRectifiedImages);
   cam_info_received = true;
   cam_info_sub.shutdown();
 }