	void publish_tf(const std::string & frame, const ros::Time & time) {

		Sophus::SE3f Mob = camera_position;

		geometry_msgs::TransformStamped tr;

		tf::quaternionEigenToMsg(Mob.unit_quaternion().cast<double>(),
				tr.transform.rotation);
		tf::vectorEigenToMsg(Mob.translation().cast<double>(),
				tr.transform.translation);

		tr.header.frame_id = "world";
		tr.header.stamp = time;
		tr.child_frame_id = "camera_rgb_optical_frame";

		br.sendTransform(tr);

	}