void VelocityCurtainNodelet::onInit() {
  ros::NodeHandle node(getNodeHandle());
  ros::NodeHandle private_node(getPrivateNodeHandle());

  double width(0.5);
  private_node.param("robot_width", width, 0.5);
  double depth(0.5);
  private_node.param("robot_depth", depth, 0.5);
  double height(1.5);
  private_node.param("robot_height", height, 1.5);
  double keep_duration(1.0);
  private_node.param("keep_duration", keep_duration, 1.0);

  std::string base_frame("base_link");
  private_node.param<std::string>("base_frame_id", base_frame, "base_link");

  using Eigen::Vector4f;

  robot_ = boost::shared_ptr<BoxRobotBody>(
      new BoxRobotBody(Vector4f(-depth/2, -width/2, 0.0, 0.0),
                       Vector4f(depth/2, width/2, height, 0.0)));

  filter_ = boost::shared_ptr<ForwardVelocityFilter>(
      new ForwardVelocityFilter(node,
                                "input_velocity",
                                "output_velocity",
                                10));
  curtain_ = boost::shared_ptr<LightCurtain>(
      new LightCurtain(
          boost::bind(&BoxRobotBody::isCollided, robot_, _1),
          boost::bind(&ForwardVelocityFilter::set_danger, filter_, _1),
          keep_duration));

  pointcloud_updater_ = boost::shared_ptr<PointCloudROS>(
      new PointCloudROS(
          node,
          "/curtain/points",
          base_frame,
          boost::bind(&LightCurtain::updatePointCloud, curtain_, _1)));

  laser_updater_ = boost::shared_ptr<LaserROS>(
      new LaserROS(
          node,
          "/curtain/scan",
          base_frame,
          boost::bind(&LightCurtain::updatePointCloud, curtain_, _1)));

  // this calls callback now, is this bug?
  config_server_ = boost::shared_ptr<ConfigServer>(new ConfigServer);
  config_server_->setCallback(boost::bind(&VelocityCurtainNodelet::reconfigureCallback, this, _1, _2));

  // set again because above bug reset the params
  robot_->setMinPoint(Vector4f(-depth/2,
			       -width/2,
			       0.0,
			       0.0));
  robot_->setMaxPoint(Vector4f(depth/2,
			       width/2,
			       height,
			       0.0));

  curtain_->setKeepDuration(keep_duration);
  pointcloud_updater_->setBaseFrameId(base_frame);
  laser_updater_->setBaseFrameId(base_frame);
  
  pointcloud_updater_->init();
  laser_updater_->init();
  curtain_->init();
}