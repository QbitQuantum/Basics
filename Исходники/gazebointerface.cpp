bool GazeboInterface::readJointStates()
{
	if(!ROSControlInterface::readJointStates())
		return false;

	if(m_last_modelStates)
	{
		std::vector<std::string>::const_iterator it = std::find(
			m_last_modelStates->name.begin(), m_last_modelStates->name.end(),
			m_modelName
		);

		if(it != m_last_modelStates->name.end())
		{
			int idx = it - m_last_modelStates->name.begin();

			//
			// Orientation feedback
			//

			// Retrieve the robot pose
			const geometry_msgs::Pose& pose = m_last_modelStates->pose[idx];

			// Set the robot orientation
			Eigen::Quaterniond quat;
			tf::quaternionMsgToEigen(pose.orientation, quat);
			quat.normalize();
			m_model->setRobotOrientation(quat);

			// Provide /odom if wanted. Convention: /odom is on the floor.
			if(m_publishOdom && m_last_modelStatesStamp - m_initTime > ros::Duration(3.0))
			{
				tf::StampedTransform trans;
				trans.frame_id_ = "/odom";
				trans.child_frame_id_ = "/ego_rot";
				trans.stamp_ = m_last_modelStatesStamp;
				trans.setIdentity();

				tf::Vector3 translation;
				tf::pointMsgToTF(pose.position, translation);

				trans.setOrigin(translation);

				Eigen::Quaterniond rot;
				rot = Eigen::AngleAxisd(m_model->robotEYaw(), Eigen::Vector3d::UnitZ());

				tf::Quaternion quat;
				tf::quaternionEigenToTF(rot, quat);

				trans.setRotation(quat);

				ROS_DEBUG("robot pos: Z = %f, yaw: %f, stamp: %f", translation.z(), m_model->robotEYaw(), trans.stamp_.toSec());
				ROS_DEBUG("robot pos tf: %f %f %f %f %f %f %f",
					trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z(),
					trans.getRotation().w(), trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z()
				);

				m_pub_tf.sendTransform(trans);
			}

			//
			// Angular velocity feedback
			//

			// Retrieve the robot twist
			const geometry_msgs::Twist& twist = m_last_modelStates->twist[idx];

			// Retrieve the robot angular velocity in global coordinates
			Eigen::Vector3d globalAngularVelocity;
			tf::vectorMsgToEigen(twist.angular, globalAngularVelocity);

			// Set the measured angular velocity (local coordinates)
			m_model->setRobotAngularVelocity(quat.conjugate() * globalAngularVelocity);

			//
			// Acceleration feedback
			//

			// We'd need an extra Gazebo plugin for acceleration sensing.
			// For now we can do without and simply calculate the current
			// acceleration due to gravity (neglect inertial accelerations).
			Eigen::Vector3d globalGravityAcceleration(0.0, 0.0, 9.81);

			// Set the measured acceleration (local coordinates)
			m_model->setAccelerationVector(quat.conjugate() * globalGravityAcceleration);

			//
			// Magnetic field vector feedback
			//

			// We assume that north is positive X. The values of 0.20G (horiz)
			// and 0.44G (vert) are approximately valid for central europe.
			Eigen::Vector3d globalMagneticVector(0.20, 0.00, -0.44); // In gauss

			// Set the measured magnetic field vector (local coordinates)
			m_model->setMagneticFieldVector(quat.conjugate() * globalMagneticVector);
		}
	}

	// Return success
	return true;
}