  int init()
  {
    // Use global namespace for node
    node_ = ros::NodeHandlePtr(new ros::NodeHandle());
    // Get tf_prefix from global namespace
    node_->param("tf_prefix", tf_prefix_, std::string(""));

    // Use private namespace for parameters
    pnode_ = ros::NodeHandlePtr(new ros::NodeHandle("~"));
    pnode_->param("publish_rate", publish_rate_, PUBLISH_RATE);

    pnode_->param("fixed_frame_id", fixed_frame_id_, std::string("odom"));
    fixed_frame_id_ = tf::resolve(tf_prefix_, fixed_frame_id_);

    pnode_->param("publish_odom_tf", publish_odom_tf_, true);

    pnode_->param("crio/ip", crio_ip_, std::string("127.0.0.1"));
    pnode_->param("crio/command_port", crio_cmd_port_, std::string("39000"));
    pnode_->param("crio/state_port", crio_state_port_, std::string("39001"));
    pnode_->param("crio/socket_timeout", socket_timeout_, 10);

    VehicleKinematics::Parameters kin_params;
    tfScalar minimum_radius_outer;

    if (!pnode_->getParam("kinematics/frame_id", kin_params.frame_id))
    {
      ROS_WARN_STREAM(pnode_->getNamespace() << "/kinematics/frame_id parameter is not set");
    }
    else
    {
      kin_params.frame_id = tf::resolve(tf_prefix_, kin_params.frame_id);
    }

    if (!pnode_->getParam("kinematics/wheelbase", kin_params.wheelbase_length))
    {
      ROS_FATAL_STREAM(pnode_->getNamespace() << "/kinematics/wheelbase parameter is not set");
      return -1;
    }
    if (!pnode_->getParam("kinematics/track", kin_params.track_width))
    {
      ROS_FATAL_STREAM( pnode_->getNamespace() << "/kinematics/track parameter is not set");
      return -1;
    }
    if (!pnode_->getParam("kinematics/rotation_center", kin_params.rotation_center))
    {
      ROS_WARN_STREAM(
          pnode_->getNamespace()
          << "/kinematics/rotation_center parameter is not set. Using default: wheelbase/2 = "
          << kin_params.wheelbase_length / 2);
      kin_params.rotation_center = kin_params.wheelbase_length / 2;
    }
    if (!pnode_->getParam("kinematics/minimum_radius_outer", minimum_radius_outer))
    {
      ROS_FATAL_STREAM(pnode_->getNamespace() << "/kinematics/minimum_radius_outer parameter is not set");
      return -1;
    }
    else
    {
      kin_params.minimum_radius = minimum_radius_outer - kin_params.track_width / 2;
    }
    if (!pnode_->getParam("kinematics/steering_ratio", kin_params.steering_ratio))
    {
      ROS_FATAL_STREAM(pnode_->getNamespace() << "/kinematics/steering_ratio parameter is not set");
      return -1;
    }

//    kin_(2.7, 1.626, 1.35);
    kin_ = boost::make_shared<VehicleKinematics>(kin_params);

    sub_ = node_->subscribe<kut_ugv_msgs::MotionCommandStamped>("motion_command", 200,
                                                                &CompactRIOCommunicationNode::motionCommand, this);
    odom_pub_ = node_->advertise<nav_msgs::Odometry>("odom", 200);
    state_pub_ = node_->advertise<kut_ugv_vehicle::StateStamped>("state", 200);

    tf_br_ = boost::shared_ptr<tf::TransformBroadcaster>(new tf::TransformBroadcaster);

    timeout_ = boost::posix_time::seconds(socket_timeout_);
    send_ep_ = udp::endpoint(boost::asio::ip::address::from_string(crio_ip_), std::atoi(crio_cmd_port_.c_str()));
    receive_ep_ = udp::endpoint(udp::v4(), std::atoi(crio_state_port_.c_str()));

    socket_.open(udp::v4());

    deadline_.expires_at(boost::posix_time::pos_infin);
    this->deadlineCallback(deadline_, socket_);

    return 0;
  }