	/**
	 * @brief Send velocity to FCU velocity controller
	 *
	 * @warning Send only VX VY VZ. ENU frame.
	 */
	void send_setpoint_velocity(const ros::Time &stamp, Eigen::Vector3d &vel_enu, double yaw_rate)
	{
		/**
		 * Documentation start from bit 1 instead 0;
		 * Ignore position and accel vectors, yaw.
		 */
		uint16_t ignore_all_except_v_xyz_yr = (1 << 10) | (7 << 6) | (7 << 0);
		auto vel = [&] () {
			if (mav_frame == MAV_FRAME::BODY_NED || mav_frame == MAV_FRAME::BODY_OFFSET_NED) {
				return ftf::transform_frame_baselink_aircraft(vel_enu);
			} else {
				return ftf::transform_frame_enu_ned(vel_enu);
			}
		} ();

		auto yr = ftf::transform_frame_baselink_aircraft(Eigen::Vector3d(0.0, 0.0, yaw_rate));

		set_position_target_local_ned(stamp.toNSec() / 1000000,
					utils::enum_value(mav_frame),
					ignore_all_except_v_xyz_yr,
					Eigen::Vector3d::Zero(),
					vel,
					Eigen::Vector3d::Zero(),
					0.0, yr.z());
	}