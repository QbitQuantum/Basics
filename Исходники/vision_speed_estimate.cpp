	/**
	 * @brief Send vision speed estimate to FCU velocity controller
	 */
	void send_vision_speed(const geometry_msgs::Vector3 &vel_enu, const ros::Time &stamp)
	{
		Eigen::Vector3d vel_;
		tf::vectorMsgToEigen(vel_enu, vel_);
		//Transform from ENU to NED frame
		auto vel = ftf::transform_frame_enu_ned(vel_);

		vision_speed_estimate(stamp.toNSec() / 1000, vel);
	}