void OdometryRemap::torsoOdomCallback(const nao_msgs::TorsoOdometryConstPtr& msgOdom, const nao_msgs::TorsoIMUConstPtr& msgIMU){
	if (m_paused){
		ROS_DEBUG("Skipping odometry callback, paused");
		return;
	}

	double odomTime = (msgOdom->header.stamp).toSec();
	ROS_DEBUG("Received [%f %f %f %f (%f/%f) (%f/%f) %f]", odomTime, msgOdom->x, msgOdom->y, msgOdom->z, msgOdom->wx, msgIMU->angleX, msgOdom->wy, msgIMU->angleY, msgOdom->wz);

	double dt = (odomTime - m_lastOdomTime);


	tf::Quaternion q;
	// roll and pitch from IMU, yaw from odometry:
	if (m_useIMUAngles)
		q.setRPY(msgIMU->angleX, msgIMU->angleY, msgOdom->wz);
	else
		q.setRPY(msgOdom->wx, msgOdom->wy, msgOdom->wz);


	m_odomPose.setOrigin(tf::Vector3(msgOdom->x, msgOdom->y, msgOdom->z));
	m_odomPose.setRotation(q);

	// apply offset transformation:
	tf::Pose transformedPose;

	if(m_mustUpdateOffset) {
        if(!m_isInitialized) {
            if(m_initializeFromIMU) {
                // Initialization from IMU: Take x, y, z, yaw from odometry, roll and pitch from IMU
                m_targetPose.setOrigin(m_odomPose.getOrigin());
                m_targetPose.setRotation(tf::createQuaternionFromRPY(msgIMU->angleX, msgIMU->angleY, msgOdom->wz));
            } else if(m_initializeFromOdometry) {
                m_targetPose.setOrigin(m_odomPose.getOrigin());
                m_targetPose.setRotation(tf::createQuaternionFromRPY(msgOdom->wx, msgOdom->wy, msgOdom->wz));
            }
            m_isInitialized = true;
        } else {
            // Overwrite target pitch and roll angles with IMU data
            const double target_yaw = tf::getYaw(m_targetPose.getRotation());
            if(m_initializeFromIMU) {
                m_targetPose.setRotation(tf::createQuaternionFromRPY(msgIMU->angleX, msgIMU->angleY, target_yaw));
            } else if(m_initializeFromOdometry){
                m_targetPose.setRotation(tf::createQuaternionFromRPY(msgOdom->wx, msgOdom->wy, target_yaw));
            }
        }
 		m_odomOffset = m_targetPose * m_odomPose.inverse();
		transformedPose = m_targetPose;
		m_mustUpdateOffset = false;
	} else {
	    transformedPose = m_odomOffset * m_odomPose;
	}

	// publish the transform over tf first:
	m_odomTransformMsg.header.stamp = msgOdom->header.stamp;
	tf::transformTFToMsg(transformedPose, m_odomTransformMsg.transform);
	m_transformBroadcaster.sendTransform(m_odomTransformMsg);

	//next, publish the actual odometry message:
	m_odom.header.stamp = msgOdom->header.stamp;
	m_odom.header.frame_id = m_odomFrameId;


	//set the velocity first (old values still valid)
	m_odom.twist.twist.linear.x = (msgOdom->x - m_odom.pose.pose.position.x) / dt;
	m_odom.twist.twist.linear.y = (msgOdom->y - m_odom.pose.pose.position.y) / dt;
	m_odom.twist.twist.linear.z = (msgOdom->z - m_odom.pose.pose.position.z) / dt;
	// TODO: calc angular velocity!
//	m_odom.twist.twist.angular.z = vth; ??

	//set the position from the above calculated transform
	m_odom.pose.pose.orientation = m_odomTransformMsg.transform.rotation;
	m_odom.pose.pose.position.x = m_odomTransformMsg.transform.translation.x;
	m_odom.pose.pose.position.y = m_odomTransformMsg.transform.translation.y;
	m_odom.pose.pose.position.z = m_odomTransformMsg.transform.translation.z;

	//publish the message
	m_odomPub.publish(m_odom);

	m_lastOdomTime = odomTime;

	// TODO: not used
//	m_lastWx = msgOdom->wx;
//	m_lastWy = msgOdom->wy;
//	m_lastWz = msgOdom->wz;
}