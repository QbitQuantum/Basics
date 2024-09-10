void ImuFilter::imuMagCallback(
	const ImuMsg::ConstPtr& imu_msg_raw,
	const MagMsg::ConstPtr& mag_msg)
{
	boost::mutex::scoped_lock(mutex_);

	const geometry_msgs::Vector3& ang_vel = imu_msg_raw->angular_velocity;
	const geometry_msgs::Vector3& lin_acc = imu_msg_raw->linear_acceleration;
	const geometry_msgs::Vector3& mag_fld = mag_msg->vector;

	ros::Time time = imu_msg_raw->header.stamp;
	imu_frame_ = imu_msg_raw->header.frame_id;

	if (!initialized_)
	{
		// initialize roll/pitch orientation from acc. vector    
		double sign = copysignf(1.0, lin_acc.z);
		double roll = atan2(lin_acc.y, sign * sqrt(lin_acc.x*lin_acc.x + lin_acc.z*lin_acc.z));
		double pitch = -atan2(lin_acc.x, sqrt(lin_acc.y*lin_acc.y + lin_acc.z*lin_acc.z));
		double yaw = 0.0; // TODO: initialize from magnetic raeding?

		tf::Quaternion init_q = tf::createQuaternionFromRPY(roll, pitch, yaw);

		q1 = init_q.getX();
		q2 = init_q.getY();
		q3 = init_q.getZ();
		q0 = init_q.getW();

		w_bx_ = 0;
		w_by_ = 0;
		w_bz_ = 0;

		last_time_ = time;
		initialized_ = true;
	}

	// determine dt: either constant, or from IMU timestamp
	float dt;
	if (constant_dt_ > 0.0)
		dt = constant_dt_;
	else
		dt = (time - last_time_).toSec();

	last_time_ = time;

	madgwickAHRSupdate(
		ang_vel.x, ang_vel.y, ang_vel.z,
		lin_acc.x, lin_acc.y, lin_acc.z,
		mag_fld.x, mag_fld.y, mag_fld.z,
		dt);

	publishFilteredMsg(imu_msg_raw);
	if (publish_tf_)
		publishTransform(imu_msg_raw);
}