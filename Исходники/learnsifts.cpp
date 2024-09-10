void cam_info_callback(const sensor_msgs::CameraInfo &msg)
{
    tgCamParams = TomGine::tgCamera::Parameter(msg);
    ROS_INFO("Camera parameters received.");
    camera_info = msg;
    need_cam_init = false;
    cam_info_sub.shutdown();
}