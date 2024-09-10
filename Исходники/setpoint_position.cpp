	/**
	 * Send transform to FCU position controller
	 *
	 * Note: send only XYZ, Yaw
	 */
	void send_setpoint_transform(const tf::Transform &transform, const ros::Time &stamp) {
		// ENU frame
		tf::Vector3 origin = transform.getOrigin();
		tf::Quaternion q = transform.getRotation();

		/* Documentation start from bit 1 instead 0,
		 * Ignore velocity and accel vectors, yaw rate
		 */
		uint16_t ignore_all_except_xyz_y = (1 << 11) | (7 << 6) | (7 << 3);

		if (uas->is_px4()) {
			/**
			 * Current PX4 has bug: it cuts throttle if there no velocity sp
			 * Issue #273.
			 *
			 * @todo Revesit this quirk later. Should be fixed in firmware.
			 */
			ignore_all_except_xyz_y = (1 << 11) | (7 << 6);
		}

		// ENU->NED. Issue #49.
		set_position_target_local_ned(stamp.toNSec() / 1000000,
				MAV_FRAME_LOCAL_NED,
				ignore_all_except_xyz_y,
				origin.y(), origin.x(), -origin.z(),
				0.0, 0.0, 0.0,
				0.0, 0.0, 0.0,
				tf::getYaw(q), 0.0);
	}